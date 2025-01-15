#include "cube_map.hpp"
#include <glm/fwd.hpp>
#include <filesystem>
#include <string>
#include <vector>
#include <iostream>
#include <functional>

// this is how cube map images are connected together
// when you place them in theis format and create a box
// then all the images connect on their seams
//
//              |---------|
//              |         |
//              |    U    |
//              |         |
//    |---------|---------|---------|---------|
//    |         |         |         |         |
//    |    L    |    F    |    R    |    B    |
//    |         |         |         |         |
//    |---------|---------|---------|---------|
//              |         |
//              |    D    |
//              |         |
//              |---------|
//


std::vector<glm::vec2> base_texture_coordinates = {
    {0.0f, 0.0f}, // Bottom-left
    {1.0f, 0.0f}, // Bottom-right
    {1.0f, 1.0f}, // Top-right
    {1.0f, 1.0f}, // Top-right (repeated for triangle)
    {0.0f, 1.0f}, // Top-left
    {0.0f, 0.0f}  // Bottom-left (repeated for triangle)
};

std::vector<glm::vec3> cube_vertex_positions_ = {{-1.0f, -1.0f, 1.0f},  // 0  Coordinates
                                                 {1.0f, -1.0f, 1.0f},   // 1       7--------6
                                                 {1.0f, -1.0f, -1.0f},  // 2      /|       /|
                                                 {-1.0f, -1.0f, -1.0f}, // 3     4--------5 |
                                                 {-1.0f, 1.0f, 1.0f},   // 4     | |      | |
                                                 {1.0f, 1.0f, 1.0f},    // 5     | 3------|-2
                                                 {1.0f, 1.0f, -1.0f},   // 6     |/       |/
                                                 {-1.0f, 1.0f, -1.0f}}; // 7     0--------1

// therefore based on the UV ordering given above and the cube vertex positions given above, this vertex ordering will
// allow the images to line up properly
// L: 0 3 7 7 4 0
// F: 3 2 6 6 7 3
// R: 2 1 5 5 6 2
// B: 1 0 4 4 5 1
// U: 7 6 5 5 4 7
// D: 0 1 2 2 3 0


CubeMap::CubeMap(const std::filesystem::path &cube_map_dir, const std::string &file_extension, TexturePacker &texture_packer)
    : cube_map_dir(cube_map_dir), file_extension(file_extension), texture_packer(texture_packer),
      top_face(create_face("up", {7, 6, 5, 5, 4, 7})), bottom_face(create_face("down", {0, 1, 2, 2, 3, 0})),
      left_face(create_face("left", {0, 3, 7, 7, 4, 0})), right_face(create_face("right", {2, 1, 5, 5, 6, 2})),
      front_face(create_face("front", {3, 2, 6, 6, 7, 3})), back_face(create_face("back", {1, 0, 4, 4, 5, 1})) {}

IVPTexturePacked CubeMap::create_face(const std::string &face_name, const std::vector<unsigned int> &face_indices) {
    auto create_path = [&](const std::string &file_name) {
        return (cube_map_dir / (file_name + "." + file_extension)).string();
    };

    auto extract_face_vertices = [&](const std::vector<unsigned int> &indices) {
        std::vector<glm::vec3> vertices;
        for (auto index : indices) {
            vertices.push_back(cube_vertex_positions_[index]);
        }
        return vertices;
    };

    std::string texture_path = create_path(face_name);
    std::cout << "cubemap texpath: " << texture_path << std::endl;
    int packed_texture_index = texture_packer.get_packed_texture_index_of_texture(texture_path);
    std::vector<glm::vec2> packed_coordinates =
        texture_packer.get_packed_texture_coordinates(texture_path, base_texture_coordinates);

    int packed_texture_bounding_box_index =
        texture_packer.get_packed_texture_bounding_box_index_of_texture(texture_path);

    std::vector<unsigned int> square_indices = {0, 1, 2, 3, 4, 5};

    return IVPTexturePacked(square_indices, extract_face_vertices(face_indices), base_texture_coordinates,
                            packed_coordinates, packed_texture_index, packed_texture_bounding_box_index, texture_path);
}

void CubeMap::regenerate() {
    top_face = create_face("up", {7, 6, 5, 5, 4, 7});
    bottom_face = create_face("down", {0, 1, 2, 2, 3, 0});
    left_face = create_face("left", {0, 3, 7, 7, 4, 0});
    right_face = create_face("right", {2, 1, 5, 5, 6, 2});
    front_face = create_face("front", {3, 2, 6, 6, 7, 3});
    back_face = create_face("back", {1, 0, 4, 4, 5, 1});
}
