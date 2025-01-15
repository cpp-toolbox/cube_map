#ifndef CUBEMAP_HPP
#define CUBEMAP_HPP

#include <filesystem>
#include <string>
#include "sbpt_generated_includes.hpp"

class CubeMap {
  public:
    CubeMap(const std::filesystem::path &cube_map_dir, const std::string &file_extension, TexturePacker &texture_packer);
    IVPTexturePacked create_face(const std::string &face_name, const std::vector<unsigned int> &face_indices);

    void regenerate();

    const std::string file_extension;
    const std::filesystem::path cube_map_dir;
    TexturePacker &texture_packer;
    IVPTexturePacked top_face;
    IVPTexturePacked bottom_face;
    IVPTexturePacked left_face;
    IVPTexturePacked right_face;
    IVPTexturePacked front_face;
    IVPTexturePacked back_face;
};

#endif // CUBEMAP_HPP