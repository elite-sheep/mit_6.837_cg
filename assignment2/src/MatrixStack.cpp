#include "MatrixStack.h"

#include <iostream>

MatrixStack::MatrixStack()
{
	// Initialize the matrix stack with the identity matrix.
  m_matrices.push_back(Matrix4f::identity());
}

void MatrixStack::clear()
{
	// Revert to just containing the identity matrix.
  
  m_matrices.clear();
  m_matrices.push_back(Matrix4f::identity());
}

Matrix4f MatrixStack::top()
{
	// Return the top of the stack
  if (!m_matrices.size()) {
    std::cerr << "MatrixStack: No matrix in the stack, please debug this error.";
    return Matrix4f();
  }
	return m_matrices[m_matrices.size() - 1];
}

void MatrixStack::push( const Matrix4f& m )
{
	// Push m onto the stack.
	// Your stack should have OpenGL semantics:
	// the new top should be the old top multiplied by m

  Matrix4f currentStateMatrix = top();
  m_matrices.push_back(m * currentStateMatrix);
}

void MatrixStack::pop()
{
  // When our stack only contains identity matrix
  // Ingnore this function call.
  if (m_matrices.size() == 1) {
    std::cout << "MatrixStack: No transformation is in the stack.";
    return;
  }

  m_matrices.pop_back();
}
