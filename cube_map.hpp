#ifndef CUBEMAP_HPP
#define CUBEMAP_HPP

#include <string>
#include "sbpt_generated_includes.hpp"

class CubeMap {
  public:
    CubeMap(const std::string &cube_map_dir, const std::string &file_extension, TexturePacker &texture_packer);
    IVPTexturePacked create_face(const std::string &face_name, const std::vector<unsigned int> &face_indices);

    void regenerate();

    const std::string file_extension;
    const std::string cube_map_dir;
    // wow I can't believe I didn't know this till now, you must store as a reference or its copied (facepalm)
    TexturePacker &texture_packer;
    IVPTexturePacked top_face;
    IVPTexturePacked bottom_face;
    IVPTexturePacked left_face;
    IVPTexturePacked right_face;
    IVPTexturePacked front_face;
    IVPTexturePacked back_face;
};

#endif // CUBEMAP_HPP
