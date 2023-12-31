#ifndef OBJECT_H
#define OBJECT_H

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>

class Object{
    protected:
        glm::vec3 pos;
        glm::vec3 scale;
        glm::vec3 rotation;

        glm::mat4 model;
        glm::mat4 normalModel;        
        
        glm::vec3 forward;
        glm::vec3 up;
        glm::vec3 right;

        void calculateVectors();
        void updateModelView();

    public:
        Object();
        Object(
            glm::vec3 _pos,
            glm::vec3 _scale,
            glm::vec3 _rotation
        );

        void moveForward(float dist);

        void setPos(glm::vec3 _pos);
        void setScale(glm::vec3 _scale);
        void setRotation(glm::vec3 _rotation);
        glm::vec3 getPos(){return pos;}
        glm::vec3 getScale(){return scale;}
        glm::vec3 getRotation(){return rotation;}
        void move(glm::vec3 vec);
        void rotate(glm::vec3 _rotation);
};

#endif