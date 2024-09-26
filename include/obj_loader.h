#pragma once

#include <fstream>
#include <glm/glm.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class ObjLoader {
public:
  ObjLoader() = default;
  ~ObjLoader() = delete;

  static void LoadObj(std::vector<glm::vec3> &outVertices,
                      std::vector<glm::vec2> &outTextures,
                      std::vector<glm::vec3> &outNormals,
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
      }
    }

    inFile.close();
  }
};
