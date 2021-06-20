#include "Plateau.h"

Plateau::Plateau(double length, double width, double height) : SceneObject()
{
    body = Cuboid(-1, -1, 0, 1, 1, 1);
    // Width and length scales in two directions so value/2,height goes only above 0 so * 1
    body.Scale((length / 2), (width / 2), (height));

    ID = Get_total();

    File_path = "../data/Plateau" + std::to_string(ID) + ".dat";

    Write_to_file();
}

bool Plateau::Set_in_scene(double x, double y, double orientation_angle)
{
    Matrix3x3 t;
    set_Rotation_OZ(t, orientation_angle);

    Move(t, Vector3D({x, y, 0}));

    Cuboid temp = body;

    temp.Rotation(orientation);
    temp.Translate(position);

    for (int i = 0; i < 8; ++i)
    {
        if (border[0] > temp[i][0] || (i == 0))
            border[0] = temp[i][0];

        if (border[1] < temp[i][0] || (i == 0))
            border[1] = temp[i][0];

        if (border[2] > temp[i][1] || (i == 0))
            border[2] = temp[i][1];

        if (border[3] < temp[i][1] || (i == 0))
            border[3] = temp[i][1];
    }
    std::cout << "Border values:" << std::endl;
    std::cout << border << std::endl;

    Write_to_file();

    return true;
}

void Plateau::Write_to_file() const
{
    Cuboid temp = body;
    Matrix3x3 temp_m = orientation;

    temp.Rotation(temp_m);
    temp.Translate(position);

    temp.Write_to_file(File_path, Overwrite);
}

std::string Plateau::Get_file_path() const
{
    return std::string(File_path);
}

std::string Plateau::Get_typeID() const
{
    return std::string(" Plateau ID :" + std::to_string(ID));
}