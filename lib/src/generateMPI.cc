/*--------------------------------------------------------------------------
  Author: Mengchi Zhang
  
  Institute: Center for Computational Neuroscience and Robotics
  University of Sussex
  Falmer, Brighton BN1 9QJ, UK 
  
  email to:  zhan2308@purdue.edu
  
  initial version: 2017-07-19
  
  --------------------------------------------------------------------------*/

//-----------------------------------------------------------------------
/*!  \file generateMPI.cc

  \brief Contains functions to generate code for running the
  simulation with MPI. Part of the code generation section.
*/
//--------------------------------------------------------------------------

#include "generateMPI.h"
#include "codeStream.h"

//--------------------------------------------------------------------------
/*!
  \brief A function that generates predominantly MPI infrastructure code.

  In this function MPI infrastructure code are generated,
  including: MPI send and receive functions.
*/
//--------------------------------------------------------------------------
void genMPI(const NNmodel &model, //!< Model description
               const string &path) //!< Path for code generationn
{
    //=======================
    // generate infraMPI.h
    //=======================

    // this file contains helpful macros and is separated out so that it can also be used by other code that is compiled separately
    string infraMPIName= path + "/" + model.getName() + "_CODE/infraMPI.h";
    ofstream fs;
    fs.open(infraMPIName.c_str());

    // Attach this to a code stream
    CodeStream os(fs);

    writeHeader(os);
    os << std::endl;

    // TODO: lack of doxygen comment

    os << "#ifndef INFRAMPI_H" << std::endl;
    os << "#define INFRAMPI_H" << std::endl;
    os << std::endl;

#ifdef MPI_ENABLE
    os << "#include <mpi.h>" << std::endl;
#endif

    os << "// ------------------------------------------------------------------------" << std::endl;
    os << "// copying things to remote node" << std::endl;
    os << std::endl;
    for(const auto &s : model.getLocalSynapseGroups()) {
        os << "#define push" << s.first << "ToRemote push" << s.first << "StateToRemote" << std::endl;
        os << "void push" << s.first << "StateToRemote();" << std::endl;
    }
    os << std::endl;

    os << "#endif" << std::endl;
    fs.close();
}
