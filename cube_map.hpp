#ifndef CUBEMAP_HPP
#define CUBEMAP_HPP

#include <filesystem>
#include <string>
#include "sbpt_generated_includes.hpp"

class CubeMap {
  public:
    CubeMap(const std::filesystem::path &cube_map_dir, const std::string &file_extension,
            TexturePacker &texture_packer);
    draw_info::IVPTexturePacked create_face(const std::string &face_name,
                                            const std::vector<unsigned int> &face_indices);

    void regenerate();

    const std::string file_extension;
    const std::filesystem::path cube_map_dir;
    TexturePacker &texture_packer;
    draw_info::IVPTexturePacked top_face;
    draw_info::IVPTexturePacked bottom_face;
    draw_info::IVPTexturePacked left_face;
    draw_info::IVPTexturePacked right_face;
    draw_info::IVPTexturePacked front_face;
    draw_info::IVPTexturePacked back_face;
};

#endif // CUBEMAP_HPP
