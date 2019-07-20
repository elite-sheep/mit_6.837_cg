#include "SkeletalModel.h"

#include <fstream>
#include <FL/Fl.H>
#include <iostream>

using namespace std;

void SkeletalModel::load(const char *skeletonFile, const char *meshFile, const char *attachmentsFile)
{
	loadSkeleton(skeletonFile);

	m_mesh.load(meshFile);
	m_mesh.loadAttachments(attachmentsFile, m_joints.size());

	computeBindWorldToJointTransforms();
	updateCurrentJointToWorldTransforms();
}

void SkeletalModel::draw(Matrix4f cameraMatrix, bool skeletonVisible)
{
	// draw() gets called whenever a redraw is required
	// (after an update() occurs, when the camera moves, the window is resized, etc)

	m_matrixStack.clear();
	m_matrixStack.push(cameraMatrix);

	if( skeletonVisible )
	{
		drawJoints();

		drawSkeleton();
	}
	else
	{
		// Clear out any weird matrix we may have been using for drawing the bones and revert to the camera matrix.
		glLoadMatrixf(m_matrixStack.top());

		// Tell the mesh to draw itself.
		m_mesh.draw();
	}
}

void SkeletalModel::loadSkeleton( const char* filename )
{
	// Load the skeleton from file here.
  
  std::ifstream ifs;
  ifs.open(filename);

  if (ifs.is_open()) {
    float translate_x, translate_y, translate_z;
    int parent_id;

    while (ifs >> translate_x >> translate_y >> translate_z >> parent_id) {
      Joint* joint = new Joint();
      joint->transform = Matrix4f::translation(translate_x, translate_y, translate_z);
      m_joints.push_back(joint);

      // The id if root node is -1, we will not explicitly construct
      // such a node here.
      if (parent_id >= 0 && m_joints.size() > parent_id) {
        m_joints[parent_id]->children.push_back(joint);
      } else if(parent_id >= 0){
        std::cerr << "SkeletalModel: Unable to find parent." << std::endl;
      } else {
        // The parent_id of root joint should be -1.
        m_rootJoint = joint;
      }
    }

    ifs.close();
  } else {
    std::cerr << "SkeletalModel: Unable to open the file " << filename << std::endl;
  }
}

void SkeletalModel::drawJoint(const Joint* joint) {
  if (joint == nullptr) {
    std::cerr << "SkeletalModel: draw joint failed.";
  }

  m_matrixStack.push(joint->transform);
  glLoadMatrixf(m_matrixStack.top());
  glutSolidSphere(0.025f, 12, 12);

  // Draw children of joint recursively.
  for (auto it = joint->children.begin(); it != joint->children.end(); ++it) {
    Joint* child = *it;
    drawJoint(child);
  }
  m_matrixStack.pop();
}

void SkeletalModel::drawJoints( )
{
	// Draw a sphere at each joint. You will need to add a recursive helper function to traverse the joint hierarchy.
	//
	// We recommend using glutSolidSphere( 0.025f, 12, 12 )
	// to draw a sphere of reasonable size.
	//
	// You are *not* permitted to use the OpenGL matrix stack commands
	// (glPushMatrix, glPopMatrix, glMultMatrix).
	// You should use your MatrixStack class
	// and use glLoadMatrix() before your drawing call.

  drawJoint(m_rootJoint);
}

void SkeletalModel::drawSkeleton( )
{
	// Draw boxes between the joints. You will need to add a recursive helper function to traverse the joint hierarchy.
  drawSkeleton(nullptr, m_rootJoint);
}

void SkeletalModel::drawSkeleton(const Joint* parent, const Joint* current) {
  if (current == nullptr) {
    std::cerr << "SkeletalModel: No current joint is given.";
    return;
  }

  if (parent) {
    Matrix4f m = m_matrixStack.top();
    Vector3f v(0.0, 0.0, 0.0);
    Vector4f p(0.0, 0.0, 0.0, 1.0);
    p = current->transform * p;
    v = p.xyz();
    Matrix4f scale = Matrix4f::scaling(50 * v.abs(), 1.0f, 1.0f);
    Vector3f xaxis(1.0f, 0.0f, 0.0f);
    Vector3f up = Vector3f::cross(xaxis, v);
    up.normalize();

    float theta = acos(Vector3f::dot(v, xaxis)/v.abs());
    Matrix4f rotate = Matrix4f::rotation(up, theta);
    Matrix4f translation = Matrix4f::translation(0.5 * v);

    m = m * translation;
    m = m * rotate;
    m = m * scale;

    glLoadMatrixf(m);
    glutSolidCube(.030);
  }

  m_matrixStack.push(current->transform);
  for (auto it = current->children.begin(); it != current->children.end(); ++it) {
    Joint* child = *it;
    drawSkeleton(current, child);
  }
  m_matrixStack.pop();

  return;
}

void SkeletalModel::setJointTransform(int jointIndex, float rX, float rY, float rZ)
{
	// Set the rotation part of the joint's transformation matrix based on the passed in Euler angles.
}


void SkeletalModel::computeBindWorldToJointTransforms()
{
	// 2.3.1. Implement this method to compute a per-joint transform from
	// world-space to joint space in the BIND POSE.
	//
	// Note that this needs to be computed only once since there is only
	// a single bind pose.
	//
	// This method should update each joint's bindWorldToJointTransform.
	// You will need to add a recursive helper function to traverse the joint hierarchy.

  m_matrixStack.clear();
  computeBindWorldToJointTransformsForSingleVertex(m_rootJoint);
}

void SkeletalModel::computeBindWorldToJointTransformsForSingleVertex(Joint* current_joint) {
  m_matrixStack.push(current_joint->transform);
  current_joint->bindWorldToJointTransform = m_matrixStack.top();

  for (auto it=current_joint->children.begin(); it != current_joint->children.end(); ++it) {
    computeBindWorldToJointTransformsForSingleVertex(*it);
  }

  m_matrixStack.pop();
}

void SkeletalModel::updateCurrentJointToWorldTransforms()
{
	// 2.3.2. Implement this method to compute a per-joint transform from
	// joint space to world space in the CURRENT POSE.
	//
	// The current pose is defined by the rotations you've applied to the
	// joints and hence needs to be *updated* every time the joint angles change.
	//
	// This method should update each joint's bindWorldToJointTransform.
	// You will need to add a recursive helper function to traverse the joint hierarchy.

  m_matrixStack.clear();
  updateCurrentJointToWorldTransformsForSingleVertex(m_rootJoint);
}

void SkeletalModel::updateCurrentJointToWorldTransformsForSingleVertex(Joint* current_joint) {
  m_matrixStack.push(current_joint->transform.inverse());
  current_joint->currentJointToWorldTransform = m_matrixStack.top();

  for (auto it=current_joint->children.begin(); it != current_joint->children.end(); ++it) {
    updateCurrentJointToWorldTransformsForSingleVertex(*it);
  }

  m_matrixStack.pop();
}

void SkeletalModel::updateMesh()
{
	// 2.3.2. This is the core of SSD.
	// Implement this method to update the vertices of the mesh
	// given the current state of the skeleton.
	// You will need both the bind pose world --> joint transforms.
	// and the current joint --> world transforms.
  
  for (int i = 0; i < m_mesh.bindVertices.size(); ++i) {
    Matrix4f transform_matrix = Matrix4f(0.0f);
    for (int j = 0; j < m_joints.size(); ++j) {
      Matrix4f attachment_scaling_matrix = Matrix4f::scaling(m_mesh.attachments[i][j], m_mesh.attachments[i][j], m_mesh.attachments[i][j]);
      Matrix4f current_transform_matrix = attachment_scaling_matrix * m_joints[j]->currentJointToWorldTransform * m_joints[j]->bindWorldToJointTransform;

      transform_matrix.setCol(0, transform_matrix.getCol(0) + current_transform_matrix.getCol(0));
      transform_matrix.setCol(1, transform_matrix.getCol(1) + current_transform_matrix.getCol(1));
      transform_matrix.setCol(2, transform_matrix.getCol(2) + current_transform_matrix.getCol(2));
      transform_matrix.setCol(3, transform_matrix.getCol(3) + current_transform_matrix.getCol(3));
    }
    Vector4f current_vertex = Vector4f(m_mesh.bindVertices[i], 1.0f);
    m_mesh.currentVertices[i] = (transform_matrix * current_vertex).xyz();
  }
}

