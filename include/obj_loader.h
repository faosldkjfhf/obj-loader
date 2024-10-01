#pragma once

#include "face.h"
#include <fstream>
#include <glm/glm.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class ObjLoader {
public:
  ObjLoader() = default;
  ~ObjLoader() {}

  static void LoadObj(std::vector<Face> &outVertices,
                      std::vector<unsigned int> &outIndices,
                      const std::string &filename) {
    std::ifstream inFile(filename);

    if (!inFile.is_open()) {
      std::cout << "Couldn't find " << filename << std::endl;
      return;
    }

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> textures;
    std::vector<glm::vec3> normals;

    std::string line = "";
    while (std::getline(inFile, line)) {
      if (line == "") {
        break;
      }
      // split line by space
      std::stringstream ss(line);
      std::string token = "";
      std::vector<std::string> tokens;
      char delimiter = ' ';
      while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
      }

      std::string first = tokens.at(0);
      if (first == "v") {
        vertices.push_back(glm::vec3(std::stof(tokens.at(1)),
                                     std::stof(tokens.at(2)),
                                     std::stof(tokens.at(3))));
      } else if (first == "vt") {
        textures.push_back(
            glm::vec2(std::stof(tokens.at(1)), std::stof(tokens.at(2))));
      } else if (first == "vn") {
        normals.push_back(glm::vec3(std::stof(tokens.at(1)),
                                    std::stof(tokens.at(2)),
                                    std::stof(tokens.at(3))));
      } else if (first == "mtllib") {
        // Load material file
      } else if (first == "f") {
        // Face
        std::vector<unsigned int> vPos;
        std::vector<unsigned int> tPos;
        std::vector<unsigned int> nPos;

        for (int i = 1; i < 4; i++) {
          std::stringstream ss(tokens.at(i));
          std::string token = "";
          std::vector<std::string> values;
          char delimiter = '/';
          while (std::getline(ss, token, delimiter)) {
            values.push_back(token);
          }

          vPos.push_back(std::stoul(values[0]) - 1);
          tPos.push_back(std::stoul(values[1]) - 1);
          nPos.push_back(std::stoul(values[2]) - 1);
        }

        for (int i = 0; i < vPos.size(); i++) {
          Face f(vertices[vPos[i]], textures[tPos[i]], normals[nPos[i]]);
          auto iter = std::find(outVertices.begin(), outVertices.end(), f);
          if (iter != outVertices.end()) {
            std::cout << "found" << std::endl;
            outIndices.push_back(iter - outVertices.begin());
          } else {
            outVertices.push_back(f);
            unsigned int newIndex = outVertices.size() - 1;
            outIndices.push_back(newIndex);
          }
        }
      }
    }

    std::cout << "Loaded " << filename << std::endl;
    inFile.close();
  }
};
