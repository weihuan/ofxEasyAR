/**
* Copyright (c) 2015-2016 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
* EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
* and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
*/

#ifndef __EASYAR_TARGET_HPP__
#define __EASYAR_TARGET_HPP__

#include "easyar/base.hpp"
#include "easyar/storage.hpp"
#include "easyar/matrix.hpp"

namespace EasyAR{

class ImageList;

class Target : public RefBase
{
public:
    Target();
    virtual ~Target();

    //! load named target if name is not empty, otherwise load the first target
    virtual bool load(const char* path, int storageType, const char* name = 0);
    //! id is valid (non-zero) only after a successfull load
    int id() const;
    const char* uid() const;
    const char* name() const;
    const char* metaData() const;
    //! data will be copied as string
    bool setMetaData(const char* data);
    ImageList images();
};

class TargetList : public RefBase
{
public:
    TargetList();
    virtual ~TargetList();

    bool load(const char* path, int storageType);
    int size() const;
    Target operator [](int idx);
    Target at(int idx);
    bool insert(const Target& target);
    bool erase(const Target& target);
};

class ImageTarget : public Target
{
public:
    ImageTarget();
    virtual ~ImageTarget();

    virtual bool load(const char* path, int storageType, const char* name = 0);
    Vec2F size() const;
    bool setSize(const Vec2F& size);
};

class AugmentedTarget : public RefBase
{
public:
    enum Status
    {
        kTargetStatusUnknown,
        kTargetStatusUndefined,
        kTargetStatusDetected,
        kTargetStatusTracked,
    };

    AugmentedTarget();
    virtual ~AugmentedTarget();

    virtual Status status() const;
    virtual Target target() const;
    virtual Matrix34F pose() const;
};

class AugmentedTargetList : public RefBase
{
public:
    AugmentedTargetList();
    virtual ~AugmentedTargetList();

    int size() const;
    AugmentedTarget operator [](int idx);
    AugmentedTarget at(int idx);
};

}
#endif
