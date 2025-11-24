//
// Created by Metoděj Janota on 23.11.2025.
//

#ifndef GAMESKA_CAMERA_H
#define GAMESKA_CAMERA_H

#include "../types/Vec2.h"

class Camera {
public:
    Camera(int viewportW, int viewportH);

    // nastaveni kam. na stred
    void setPosition(Vec2 pos) { m_position = pos; }
    Vec2 getPosition() const { return m_position; }
    Vec2 worldToScreen(Vec2 worldPos) const;

    bool isVisible(Vec2 worldPos) const;
    int getViewportW() const { return m_viewportW; }
    int getViewportH() const { return m_viewportH; }

private:
    // stred kam., sirka, vyska
    Vec2 m_position;
    int m_viewportW;
    int m_viewportH;
};


#endif //GAMESKA_CAMERA_H