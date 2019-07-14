#include "Mesh.h"

#include <string>

using namespace std;

void Mesh::load( const char* filename )
{
	// 2.1.1. load() should populate bindVertices, currentVertices, and faces

	// Add your code here.

  cout << "Mesh: load verticies: " << filename << endl;
  ifstream ifs;
  ifs.open(filename);

  if (ifs.is_open()) {
#define MAXSIZE 256

    char buf[MAXSIZE];
    while (ifs.getline(buf, MAXSIZE)) {
      stringstream ss(buf);
      string s;

      ss >> s;
      if (s == "v") {
        float x, y, z;
        ss >> x >> y >> z;
        bindVertices.push_back(Vector3f(x, y, z));
      } else if (s == "f") {
        unsigned x_index, y_index, z_index;
        ss >> x_index >> y_index >> z_index;
        faces.push_back(Tuple3u(x_index, y_index, z_index));
      } else {
        cerr << "Mesh: Undefined tag: " << s << endl;
      }
    }

  } else {
    cerr << "Mesh: Can not open file: " << filename << endl;
  }
  ifs.close();

	// make a copy of the bind vertices as the current vertices
	currentVertices = bindVertices;
}

void Mesh::draw()
{
	// Since these meshes don't have normals
	// be sure to generate a normal per triangle.
	// Notice that since we have per-triangle normals
	// rather than the analytical normals from
	// assignment 1, the appearance is "faceted".

  cout << "Mesh: rendering." << endl;
  glBegin(GL_TRIANGLES);
  for (auto it = faces.begin(); it != faces.end(); ++it) {
    Vector3f ba = currentVertices[(*it)[1]-1] - currentVertices[(*it)[0]-1];
    Vector3f ca = currentVertices[(*it)[2]-1] - currentVertices[(*it)[0]-1];
    Vector3f normal = Vector3f::cross(ba, ca);
    normal.normalize();

    glNormal3f(normal[0], normal[1], normal[2]);
    glVertex3f(currentVertices[(*it)[0]-1][0], currentVertices[(*it)[0]-1][1], currentVertices[(*it)[0]-1][2]);
    glNormal3f(normal[0], normal[1], normal[2]);
    glVertex3f(currentVertices[(*it)[1]-1][0], currentVertices[(*it)[1]-1][1], currentVertices[(*it)[1]-1][2]);
    glNormal3f(normal[0], normal[1], normal[2]);
    glVertex3f(currentVertices[(*it)[2]-1][0], currentVertices[(*it)[2]-1][1], currentVertices[(*it)[2]-1][2]);
  }
  glEnd();
}

void Mesh::loadAttachments( const char* filename, int numJoints )
{
	// 2.2. Implement this method to load the per-vertex attachment weights
	// this method should update m_mesh.attachments

  cout << "Mesh: load attachments: " << filename << endl;

  ifstream ifs;
  ifs.open(filename);

  if (ifs.is_open()) {
#define MAXSIZE 256
    char buf[MAXSIZE];
    while (ifs.getline(buf, MAXSIZE)) {
      stringstream ss(buf);
      float tmp_weight;
      vector<float> tmp_weight_list;

      for (int i = 0; i < numJoints; i++) {
        ss >> tmp_weight;
        tmp_weight_list.push_back(tmp_weight);
      }

      attachments.push_back(tmp_weight_list);
    }

    ifs.close();
  } else {
    cerr << "Mesh: Unable to load attachments: " << filename << endl;
  }

}
