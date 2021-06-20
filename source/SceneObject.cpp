#include "SceneObject.h"

int SceneObject::Total_scene_objects = 0;

SceneObject::SceneObject()
{
    position = Vector3D();
    orientation = Matrix3x3({1, 0, 0,
                             0, 1, 0,
                             0, 0, 1});

    Vector4D border; // x-min x-max y-min y-max

    Total_scene_objects++;
}

bool SceneObject::Move(Matrix3x3 &rotation_matrix, Vector3D translation_vector)
{
    // Since they won't move during the animation, passed values overwrite pervious position
    this->orientation = rotation_matrix;
    this->position = translation_vector;

    return true;
}

void SceneObject::Write_to_file() const
{
    std::cout << "No file to write" << std::endl;
}

std::string SceneObject::Get_file_path() const
{
    return std::string("No path specified for General object");
}

Vector3D SceneObject::Get_position() const
{
    return position;
}

std::string SceneObject::Get_typeID() const
{
    return std::string("General object");
}

bool SceneObject::Add_files_names(PzG::LaczeDoGNUPlota &Link, int colour)
{
    Link.DodajNazwePliku(File_path.c_str())
        .ZmienSposobRys(PzG::SR_Ciagly)
        .ZmienSzerokosc(2)
        .ZmienKolor(colour);

    return true;
}

bool SceneObject::Remove_files_names(PzG::LaczeDoGNUPlota &Link) const
{
    Link.UsunNazwePliku(File_path.c_str());
    remove(File_path.c_str());
    return true;
}

bool SceneObject::Check_collision(const SceneObject &obj) const
{
    if (border[0] < obj.border[1] && border[1] > obj.border[0] && border[2] < obj.border[3] && border[3] > obj.border[2])
        return true;
    else
        return false;
}