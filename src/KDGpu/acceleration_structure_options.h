/*
  This file is part of KDGpu.

  SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>

  SPDX-License-Identifier: MIT

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include <span>

#include <KDGpu/gpu_core.h>
#include <KDGpu/handle.h>

namespace KDGpu {

struct AccelerationStructure_t;
struct Buffer_t;

struct AccelerationStructureGeometryTrianglesData {
    Format vertexFormat{ Format::UNDEFINED };
    Handle<Buffer_t> vertexData;
    size_t vertexStride{ 0 };
    uint32_t maxVertex{ 0 };
    IndexType indexType{ IndexType::None };
    Handle<Buffer_t> indexData;
    Handle<Buffer_t> transformData;
};

struct AccelerationStructureGeometryAabbsData {
    Handle<Buffer_t> data;
    size_t stride{ 0 };
};

struct AccelerationStructureGeometryInstance {
    float transform[3][4]{
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f
    };
    uint32_t instanceCustomIndex : 24 = 0;
    uint32_t mask : 8 = 0xFF;
    uint32_t instanceShaderBindingTableRecordOffset : 24 = 0;
    GeometryInstanceFlags flags = GeometryInstanceFlagBits::None;
    Handle<AccelerationStructure_t> accelerationStructure;
};

struct AccelerationStructureGeometryInstancesData {
    std::vector<AccelerationStructureGeometryInstance> data;
};

using AccelerationStructureGeometry = std::variant<AccelerationStructureGeometryTrianglesData, AccelerationStructureGeometryAabbsData, AccelerationStructureGeometryInstancesData>;

struct AccelerationStructureOptions {
    std::string_view label;
    AccelerationStructureType type{ AccelerationStructureType::TopLevel };
    AccelerationStructureFlags flags{ AccelerationStructureFlagBits::None };
    struct GeometryTypeAndCount {
        AccelerationStructureGeometry geometry;
        uint32_t maxGeometryCount{ 1 };
    };
    std::vector<GeometryTypeAndCount> geometryTypesAndCount;
};

struct BuildAccelerationStructureOptions {
    struct BuildOptions {
        BuildAccelerationStructureMode mode{ BuildAccelerationStructureMode::Build };
        std::vector<AccelerationStructureGeometry> geometries;
        Handle<AccelerationStructure_t> sourceStructure;
        Handle<AccelerationStructure_t> destinationStructure;
    };
    struct BuildRangeInfo {
        uint32_t primitiveCount{ 0 };
        uint32_t primitiveOffset{ 0 };
        uint32_t firstVertex{ 0 };
        uint32_t transformOffset{ 0 };
    };

    std::vector<BuildOptions> buildGeometryInfos;
    std::vector<BuildRangeInfo> buildRangeInfos;
};

} // namespace KDGpu