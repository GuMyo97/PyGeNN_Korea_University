// Google test includes
#include "gtest/gtest.h"

// GeNN includes
#include "type.h"

// GeNN transpiler includes
#include "transpiler/errorHandler.h"
#include "transpiler/parser.h"
#include "transpiler/scanner.h"
#include "transpiler/typeChecker.h"

using namespace GeNN;
using namespace GeNN::Transpiler;

//--------------------------------------------------------------------------
// Anonymous namespace
//--------------------------------------------------------------------------
namespace
{
class TestErrorHandler : public ErrorHandler
{
public:
    TestErrorHandler() : m_Error(false)
    {}

    bool hasError() const { return m_Error; }

    virtual void error(size_t line, std::string_view message) override
    {
        report(line, "", message);
    }

    virtual void error(const Token &token, std::string_view message) override
    {
        if(token.type == Token::Type::END_OF_FILE) {
            report(token.line, " at end", message);
        }
        else {
            report(token.line, " at '" + std::string{token.lexeme} + "'", message);
        }
    }

private:
    void report(size_t line, std::string_view where, std::string_view message)
    {
        std::cerr << "[line " << line << "] Error" << where << ": " << message << std::endl;
        m_Error = true;
    }

    bool m_Error;
};

void typeCheckStatements(std::string_view code, TypeChecker::Environment &typeEnvironment)
{
    // Scan
    TestErrorHandler errorHandler;
    const auto tokens = Scanner::scanSource(code, errorHandler);
    ASSERT_FALSE(errorHandler.hasError());
 
    // Parse
    const auto statements = Parser::parseBlockItemList(tokens, errorHandler);
    ASSERT_FALSE(errorHandler.hasError());
     
    // Typecheck
    TypeChecker::typeCheck(statements, typeEnvironment, errorHandler);
    ASSERT_FALSE(errorHandler.hasError());
}

Type::QualifiedType typeCheckExpression(std::string_view code, TypeChecker::Environment &typeEnvironment)
{
    // Scan
    TestErrorHandler errorHandler;
    const auto tokens = Scanner::scanSource(code, errorHandler);
    EXPECT_FALSE(errorHandler.hasError());
 
    // Parse
    const auto expression = Parser::parseExpression(tokens, errorHandler);
    EXPECT_FALSE(errorHandler.hasError());
     
    // Typecheck
    const auto type = TypeChecker::typeCheck(expression.get(), typeEnvironment, errorHandler);
    EXPECT_FALSE(errorHandler.hasError());
    return type;
}
}   // Anonymous namespace

//--------------------------------------------------------------------------
// Tests
//--------------------------------------------------------------------------
TEST(TypeChecker, ArraySubscript)
{
    // Integer array indexing
    {
        TypeChecker::Environment typeEnvironment;
        typeEnvironment.define<Type::Int32Ptr>("intArray");
        typeCheckStatements("int x = intArray[4];", typeEnvironment);
    }
    
    // Float array indexing
    EXPECT_THROW({
        TypeChecker::Environment typeEnvironment;
        typeEnvironment.define<Type::Int32Ptr>("intArray");
        typeCheckStatements("int x = intArray[4.0f];", typeEnvironment);}, 
        TypeChecker::TypeCheckError);

    // Pointer indexing
    EXPECT_THROW({
        TypeChecker::Environment typeEnvironment;
        typeEnvironment.define<Type::Int32Ptr>("intArray");
        typeEnvironment.define<Type::Int32Ptr>("indexArray");
        typeCheckStatements("int x = intArray[indexArray];", typeEnvironment);}, 
        TypeChecker::TypeCheckError);
}
//--------------------------------------------------------------------------
TEST(TypeChecker, Assignment)
{
    // Numeric assignment
    {
        TypeChecker::Environment typeEnvironment;
        typeEnvironment.define<Type::Int32>("intVal");
        typeEnvironment.define<Type::Float>("floatVal");
        typeEnvironment.define<Type::Int32>("intValConst", true);
        typeCheckStatements(
            "int w = intVal;\n"
            "float x = floatVal;\n"
            "int y = floatVal;\n"
            "float z = intVal;\n"
            "int wc = intValConst;\n"
            "const int cw = intVal;\n"
            "const int cwc = intValConst;\n",
            typeEnvironment);
    }

    // Pointer assignement
    {
        TypeChecker::Environment typeEnvironment;
        typeEnvironment.define<Type::Int32Ptr>("intArray");
        typeEnvironment.define<Type::Int32Ptr>("intArrayConst", true);
        typeCheckStatements(
            "int *x = intArray;\n"
            "const int *y = intArray;\n"
            "const int *z = intArrayConst;\n", 
            typeEnvironment);
    }

    // Pointer assignement, attempt to remove const
    EXPECT_THROW({
        TypeChecker::Environment typeEnvironment;
        typeEnvironment.define<Type::Int32Ptr>("intArray", true);
        typeCheckStatements("int *x = intArray;", typeEnvironment);},
        TypeChecker::TypeCheckError);

    // Pointer assignement without explicit cast
    EXPECT_THROW({
        TypeChecker::Environment typeEnvironment;
        typeEnvironment.define<Type::Int32Ptr>("intArray");
        typeCheckStatements("float *x = intArray;", typeEnvironment);},
        TypeChecker::TypeCheckError);
}
//--------------------------------------------------------------------------
TEST(TypeChecker, Binary)
{
}
//--------------------------------------------------------------------------
TEST(TypeChecker, Call)
{
}
//--------------------------------------------------------------------------
TEST(TypeChecker, Cast)
{
    // Numeric cast
    {
        TypeChecker::Environment typeEnvironment;
        typeEnvironment.define<Type::Int32>("intVal");
        const auto type = typeCheckExpression("(float)intArray", typeEnvironment);
        EXPECT_EQ(type.type->getTypeHash(), Type::Float::getInstance()->getTypeHash());
        EXPECT_FALSE(type.constValue);
        EXPECT_FALSE(type.constPointer);
    }

   // Pointer cast can't reinterpret
   EXPECT_THROW({
        TypeChecker::Environment typeEnvironment;
        typeEnvironment.define<Type::Int32Ptr>("intArray");
        typeCheckExpression("(float*)intArray", typeEnvironment);},
        TypeChecker::TypeCheckError);
}
//--------------------------------------------------------------------------
TEST(TypeChecker, Conditional)
{
}
//--------------------------------------------------------------------------
TEST(TypeChecker, Literal)
{
    // Float
    {
        TypeChecker::Environment typeEnvironment;
        const auto type = typeCheckExpression("1.0f", typeEnvironment);
        EXPECT_EQ(type.type->getTypeHash(), Type::Float::getInstance()->getTypeHash());
        EXPECT_TRUE(type.constValue);
        EXPECT_FALSE(type.constPointer);
    }

    // Double
    {
        TypeChecker::Environment typeEnvironment;
        const auto type = typeCheckExpression("1.0", typeEnvironment);
        EXPECT_EQ(type.type->getTypeHash(), Type::Double::getInstance()->getTypeHash());
        EXPECT_TRUE(type.constValue);
        EXPECT_FALSE(type.constPointer);
    }

    // Integer
    {
        TypeChecker::Environment typeEnvironment;
        const auto type = typeCheckExpression("100", typeEnvironment);
        EXPECT_EQ(type.type->getTypeHash(), Type::Int32::getInstance()->getTypeHash());
        EXPECT_TRUE(type.constValue);
        EXPECT_FALSE(type.constPointer);
    }

    // Unsigned integer
    {
        TypeChecker::Environment typeEnvironment;
        const auto type = typeCheckExpression("100U", typeEnvironment);
        EXPECT_EQ(type.type->getTypeHash(), Type::Uint32::getInstance()->getTypeHash());
        EXPECT_TRUE(type.constValue);
        EXPECT_FALSE(type.constPointer);
    }
}
//--------------------------------------------------------------------------
TEST(TypeChecker, Unary)
{
    // Dereference pointer
    {
        TypeChecker::Environment typeEnvironment;
        typeEnvironment.define<Type::Int32Ptr>("intArray");
        const auto type = typeCheckExpression("*intArray", typeEnvironment);
        EXPECT_EQ(type.type->getTypeHash(), Type::Int32::getInstance()->getTypeHash());
        EXPECT_FALSE(type.constValue);
        EXPECT_FALSE(type.constPointer);
    }

    // Dereference pointer to const
    {
        TypeChecker::Environment typeEnvironment;
        typeEnvironment.define<Type::Int32Ptr>("intArray", true);
        const auto type = typeCheckExpression("*intArray", typeEnvironment);
        EXPECT_EQ(type.type->getTypeHash(), Type::Int32::getInstance()->getTypeHash());
        EXPECT_TRUE(type.constValue);
        EXPECT_FALSE(type.constPointer);
    }

    // Dereference const pointer
    {
        TypeChecker::Environment typeEnvironment;
        typeEnvironment.define<Type::Int32Ptr>("intArray", false, true);
        const auto type = typeCheckExpression("*intArray", typeEnvironment);
        EXPECT_EQ(type.type->getTypeHash(), Type::Int32::getInstance()->getTypeHash());
        EXPECT_FALSE(type.constValue);
        EXPECT_FALSE(type.constPointer);
    }

    // Dereference const pointer to const
    {
        TypeChecker::Environment typeEnvironment;
        typeEnvironment.define<Type::Int32Ptr>("intArray", true, true);
        const auto type = typeCheckExpression("*intArray", typeEnvironment);
        EXPECT_EQ(type.type->getTypeHash(), Type::Int32::getInstance()->getTypeHash());
        EXPECT_TRUE(type.constValue);
        EXPECT_FALSE(type.constPointer);
    }

    // Dereference numeric
    EXPECT_THROW({
        TypeChecker::Environment typeEnvironment;
        typeEnvironment.define<Type::Int32>("intVal");
        typeCheckExpression("*intVal", typeEnvironment); },
        TypeChecker::TypeCheckError);

    // Address of numeric
    {
        TypeChecker::Environment typeEnvironment;
        typeEnvironment.define<Type::Int32>("intVal");
        const auto type = typeCheckExpression("&intVal", typeEnvironment);
        EXPECT_EQ(type.type->getTypeHash(), Type::Int32Ptr::getInstance()->getTypeHash());
        EXPECT_FALSE(type.constValue);
        EXPECT_FALSE(type.constPointer);
    }

    // Address of pointer
    EXPECT_THROW({
        TypeChecker::Environment typeEnvironment;
        typeEnvironment.define<Type::Int32Ptr>("intArray");
        typeCheckExpression("&intArray", typeEnvironment);},
        TypeChecker::TypeCheckError);
}
