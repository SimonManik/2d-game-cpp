//
// Created by Metoděj Janota on 23.11.2025.
//

#include "Camera.h"

Camera::Camera(int viewportW, int viewportH)
    : m_position(0, 0)
    , m_viewportW(viewportW)
    , m_viewportH(viewportH) {
}

Vec2 Camera::worldToScreen(Vec2 worldPos) const {
    Vec2 offset = worldPos - m_position;
    int screenX = offset.x + m_viewportW / 2;
    int screenY = -offset.y + m_viewportH / 2;
    return Vec2(screenX, screenY);
}

bool Camera::isVisible(Vec2 worldPos) const {
    Vec2 screenPos = worldToScreen(worldPos);
    return screenPos.x >= 0 && screenPos.x < m_viewportW &&
           screenPos.y >= 0 && screenPos.y < m_viewportH;
}