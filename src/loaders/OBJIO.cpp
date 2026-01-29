#include "OBJIO.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

bool readBasicStrandOBJ(const char* filename, vector<VEC3>& verts)
{
    verts.clear();

    std::ifstream ifs(filename);
    if(!ifs.good())
    {
        std::cerr << "readBasicStrandOBJ cannot read file at path: " << filename << std::endl;
        return false;
    }

    const std::string v("v");
    const std::string l("l");

    for (std::string line; std::getline(ifs, line);)
    {
        std::istringstream iss(line);
        std::string key;
        iss >> key;
        if (key == v)
        {
            double x, y, z;
            iss >> x >> y >> z;
            verts.emplace_back(x,y,z);
        }
        else if (key == l) {}
        else
        {
            std::cerr << "Unexpected line in basic strand obj: " << line << std::endl;
        }
    }
    return true;
}

bool writeBasicStrandOBJ(const vector<VEC3>& verts, const char* filename)
{
    std::ofstream s(filename);
    if (!s.is_open())
    {
        std::cerr << "writeOBJFile cannot open at: " << filename << std::endl;
        return false;
    }

    if (verts.empty())
    {
        std::cerr << "no vertices." << std::endl;
        return false;
    }

    for (unsigned int ii = 0; ii < verts.size(); ii++)
    {
        const VEC3 vert = verts[ii];
        s << "v " << vert[0] << " " << vert[1] << " " << vert[2] << "\n";
    }
    s << "l ";
    for (unsigned int ii = 0; ii < verts.size(); ii++)
    {
        s << ii + 1 << " ";
    }
    return true;
}

bool readMultStrandOBJ(const char* filename, vector<VEC3>& vs, vector<vector<int>>& edges)
{
    std::ifstream s(filename);
    if(!s.good())
    {
        std::cerr << "readOBJFile cannot open at: " << filename << std::endl;
        return false;
    }

    vs.clear();
    edges.clear();

    const std::string v("v");
    const std::string l("l");

    for(std::string line; std::getline(s, line); )
    {
        std::istringstream is(line);
        std::string key;
        is >> key;
        if (key == v)
        {
            double x, y, z;
            is >> x >> y >> z;
            vs.emplace_back(x, y, z);
        }
        else if (key == l)
        {
            vector<int> edge;
            string str;
            while(is >> str)
            {
                edge.push_back(std::stoi(str) - 1);
            }
            edges.push_back(edge);
        }
    }
    return true;
}

bool writeMultStrandOBJ(const vector<VEC3>& vs, const vector<vector<int>>& edges, const char* filename)
{
    std::ofstream s(filename);
    if (!s.is_open())
    {
        std::cerr << "writeOBJFile cannot open at: " << filename << std::endl;
        return false;
    }

    if (vs.empty())
    {
        std::cerr << "no vertices." << std::endl;
        return false;
    }
    // if (edges.empty())
    // {
    //     std::cerr << "no edges." << std::endl;
    //     return false;
    // }

    for (unsigned int ii = 0; ii < vs.size(); ii++)
    {
        const VEC3 vert = vs[ii];
        s << "v " << vert[0] << " " << vert[1] << " " << vert[2] << "\n";
    }
    for(unsigned int i = 0; i < edges.size(); i++)
    {
        s << "l ";
        for (unsigned int ii = 0; ii < edges[i].size(); ii++)
        {
            s << edges[i][ii] + 1 << " ";
        }
        s << "\n";
    }
    return true;
}

bool writeMultStrandOBJ(const vector<vector<VEC3>>& allVs, const char* filename)
{
    vector<vector<int>> edges;
    vector<VEC3> flatVs;
    int e = 0;
    for(unsigned int i = 0; i < allVs.size(); i++)
    {
        vector<int> edge(allVs[i].size());
        for(unsigned int j = 0 ;j < edge.size(); j++)
        {
            edge[j] = e++;
            flatVs.push_back(allVs[i][j]);
        }
        edges.push_back(edge);
    }

    return writeMultStrandOBJ(flatVs, edges, filename);
}