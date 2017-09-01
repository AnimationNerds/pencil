/*

Pencil - Traditional Animation Software
Copyright (C) 2012-2017 Matthew Chiawen Chang

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; version 2 of the License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

*/

#include "camera.h"

Camera::Camera()
{
}

Camera::Camera(QPointF translation, float rotation, float scaling)
{
    mTranslate = translation;
    mRotate = rotation;
    mScale = scaling;
    updateViewTransform();
}

Camera::~Camera()
{
}

QTransform Camera::getView()
{
    if (mNeedUpdateView)
        updateViewTransform();
    return view;
}

void Camera::reset()
{
    mTranslate = QPointF(0, 0);
    mRotate = 0.f;
    mScale = 1.f;
    mNeedUpdateView = true;
}

void Camera::updateViewTransform()
{
    if (mNeedUpdateView)
    {
        QTransform t;
        t.translate(mTranslate.x(), mTranslate.y());

        QTransform r;
        r.rotate(mRotate);

        QTransform s;
        s.scale(mScale, mScale);

        view = t * r * s;
    }
    mNeedUpdateView = false;
}

void Camera::translate(float dx, float dy)
{
    mTranslate.setX(dx);
    mTranslate.setY(dy);

    mNeedUpdateView = true;
}

void Camera::rotate(float degree)
{
    mRotate = degree;
    if (mRotate > 360.f)
    {
        mRotate = mRotate - 360.f;
    }
    else if (mRotate < 0.f)
    {
        mRotate = mRotate + 360.f;
    }
    mRotate = degree;

    mNeedUpdateView = true;
}

void Camera::scale(float scaleValue)
{
    mScale = scaleValue;

    mNeedUpdateView = true;
}

bool Camera::operator==(const Camera& rhs) const
{
    bool b = (mTranslate == rhs.mTranslate)
        && qFuzzyCompare(mRotate, rhs.mRotate)
        && qFuzzyCompare(mScale, rhs.mScale);

    return b;
}
