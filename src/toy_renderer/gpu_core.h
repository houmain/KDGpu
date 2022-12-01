#pragma once

#include <stdint.h>
#include <string>

#pragma once

#define SERENITY_MAKE_API_VERSION(variant, major, minor, patch) \
    ((((uint32_t)(variant)) << 29) | (((uint32_t)(major)) << 22) | (((uint32_t)(minor)) << 12) | ((uint32_t)(patch)))

namespace ToyRenderer {

constexpr uint32_t maxAdapterNameSize = 256U;
constexpr uint32_t UuidSize = 16U;
constexpr uint32_t remainingArrayLayers = (~0U);
constexpr uint32_t remainingMipLevels = (~0U);

using DeviceSize = uint64_t;
using Flags = uint32_t;

struct Extent2D {
    uint32_t width;
    uint32_t height;
};

struct Extent3D {
    uint32_t width;
    uint32_t height;
    uint32_t depth;
};

struct Offset2D {
    int32_t x;
    int32_t y;
};

struct Offset3D {
    int32_t x;
    int32_t y;
    int32_t z;
};

struct Rect2D {
    Offset2D offset;
    Extent2D extent;
};

enum class SampleCountFlagBits {
    Samples1Bit = 0x00000001,
    Samples2Bit = 0x00000002,
    Samples4Bit = 0x00000004,
    Samples8Bit = 0x00000008,
    Samples16Bit = 0x00000010,
    Samples32Bit = 0x00000020,
    Samples64Bit = 0x00000040,
    MaxEnum = 0x7FFFFFFF
};
using SampleCountFlags = Flags;

enum class AdapterDeviceType {
    Other = 0,
    IntegratedGpu = 1,
    DiscreteGpu = 2,
    VirtualGpu = 3,
    Cpu = 4,
    MaxEnum = 0x7FFFFFFF
};

inline std::string adapterDeviceTypeToString(AdapterDeviceType deviceType)
{
    switch (deviceType) {
    case ToyRenderer::AdapterDeviceType::Other:
        return "Other Device Type";

    case ToyRenderer::AdapterDeviceType::IntegratedGpu:
        return "Integrated GPU";

    case ToyRenderer::AdapterDeviceType::DiscreteGpu:
        return "Discrete GPU";

    case ToyRenderer::AdapterDeviceType::VirtualGpu:
        return "Virtual GPU";

    case ToyRenderer::AdapterDeviceType::Cpu:
        return "CPU";

    default:
        return "Unknown device type";
    }
}

enum class QueueFlagBits {
    GraphicsBit = 0x00000001,
    ComputeBit = 0x00000002,
    TransferBit = 0x00000004,
    SparseBindingBit = 0x00000008,
    ProtectedBit = 0x00000010,
    VideoDecodeBit = 0x00000020,
    VideoEncodeBit = 0x00000040,
    MaxEnum = 0x7FFFFFFF
};
using QueueFlags = Flags;
// TODO: Use Flags<QueueFlagBits>

enum class PresentMode {
    Immediate = 0,
    Mailbox = 1,
    Fifo = 2,
    FifoRelaxed = 3,
    SharedDemandRefresh = 1000111000,
    SharedContinuousRefresh = 1000111001,
    MaxEnum = 0x7FFFFFFF
};

enum class ColorSpace {
    SRgbNonlinear = 0,
    DisplayP3Nonlinear = 1000104001,
    ExtendedSRgbLinear = 1000104002,
    DisplayP3Linear = 1000104003,
    DciP3Nonlinear = 1000104004,
    Bt709Linear = 1000104005,
    Bt709Nonlinear = 1000104006,
    Bt2020Linear = 1000104007,
    Hdr10St2084 = 1000104008,
    Dolbyvision = 1000104009,
    Hdr10Hlg = 1000104010,
    AdobergbLinear = 1000104011,
    AdobergbNonlinear = 1000104012,
    PassThrough = 1000104013,
    ExtendedSRgbNonlinear_ext = 1000104014,
    DisplayNative = 1000213000,
    DciP3Linear = DisplayP3Linear,
    MaxEnum = 0x7fffffff
};

// TODO: Normalize case of enum elements
enum class Format {
    UNDEFINED = 0,
    R4G4_UNORM_PACK8 = 1,
    R4G4B4A4_UNORM_PACK16 = 2,
    B4G4R4A4_UNORM_PACK16 = 3,
    R5G6B5_UNORM_PACK16 = 4,
    B5G6R5_UNORM_PACK16 = 5,
    R5G5B5A1_UNORM_PACK16 = 6,
    B5G5R5A1_UNORM_PACK16 = 7,
    A1R5G5B5_UNORM_PACK16 = 8,
    R8_UNORM = 9,
    R8_SNORM = 10,
    R8_USCALED = 11,
    R8_SSCALED = 12,
    R8_UINT = 13,
    R8_SINT = 14,
    R8_SRGB = 15,
    R8G8_UNORM = 16,
    R8G8_SNORM = 17,
    R8G8_USCALED = 18,
    R8G8_SSCALED = 19,
    R8G8_UINT = 20,
    R8G8_SINT = 21,
    R8G8_SRGB = 22,
    R8G8B8_UNORM = 23,
    R8G8B8_SNORM = 24,
    R8G8B8_USCALED = 25,
    R8G8B8_SSCALED = 26,
    R8G8B8_UINT = 27,
    R8G8B8_SINT = 28,
    R8G8B8_SRGB = 29,
    B8G8R8_UNORM = 30,
    B8G8R8_SNORM = 31,
    B8G8R8_USCALED = 32,
    B8G8R8_SSCALED = 33,
    B8G8R8_UINT = 34,
    B8G8R8_SINT = 35,
    B8G8R8_SRGB = 36,
    R8G8B8A8_UNORM = 37,
    R8G8B8A8_SNORM = 38,
    R8G8B8A8_USCALED = 39,
    R8G8B8A8_SSCALED = 40,
    R8G8B8A8_UINT = 41,
    R8G8B8A8_SINT = 42,
    R8G8B8A8_SRGB = 43,
    B8G8R8A8_UNORM = 44,
    B8G8R8A8_SNORM = 45,
    B8G8R8A8_USCALED = 46,
    B8G8R8A8_SSCALED = 47,
    B8G8R8A8_UINT = 48,
    B8G8R8A8_SINT = 49,
    B8G8R8A8_SRGB = 50,
    A8B8G8R8_UNORM_PACK32 = 51,
    A8B8G8R8_SNORM_PACK32 = 52,
    A8B8G8R8_USCALED_PACK32 = 53,
    A8B8G8R8_SSCALED_PACK32 = 54,
    A8B8G8R8_UINT_PACK32 = 55,
    A8B8G8R8_SINT_PACK32 = 56,
    A8B8G8R8_SRGB_PACK32 = 57,
    A2R10G10B10_UNORM_PACK32 = 58,
    A2R10G10B10_SNORM_PACK32 = 59,
    A2R10G10B10_USCALED_PACK32 = 60,
    A2R10G10B10_SSCALED_PACK32 = 61,
    A2R10G10B10_UINT_PACK32 = 62,
    A2R10G10B10_SINT_PACK32 = 63,
    A2B10G10R10_UNORM_PACK32 = 64,
    A2B10G10R10_SNORM_PACK32 = 65,
    A2B10G10R10_USCALED_PACK32 = 66,
    A2B10G10R10_SSCALED_PACK32 = 67,
    A2B10G10R10_UINT_PACK32 = 68,
    A2B10G10R10_SINT_PACK32 = 69,
    R16_UNORM = 70,
    R16_SNORM = 71,
    R16_USCALED = 72,
    R16_SSCALED = 73,
    R16_UINT = 74,
    R16_SINT = 75,
    R16_SFLOAT = 76,
    R16G16_UNORM = 77,
    R16G16_SNORM = 78,
    R16G16_USCALED = 79,
    R16G16_SSCALED = 80,
    R16G16_UINT = 81,
    R16G16_SINT = 82,
    R16G16_SFLOAT = 83,
    R16G16B16_UNORM = 84,
    R16G16B16_SNORM = 85,
    R16G16B16_USCALED = 86,
    R16G16B16_SSCALED = 87,
    R16G16B16_UINT = 88,
    R16G16B16_SINT = 89,
    R16G16B16_SFLOAT = 90,
    R16G16B16A16_UNORM = 91,
    R16G16B16A16_SNORM = 92,
    R16G16B16A16_USCALED = 93,
    R16G16B16A16_SSCALED = 94,
    R16G16B16A16_UINT = 95,
    R16G16B16A16_SINT = 96,
    R16G16B16A16_SFLOAT = 97,
    R32_UINT = 98,
    R32_SINT = 99,
    R32_SFLOAT = 100,
    R32G32_UINT = 101,
    R32G32_SINT = 102,
    R32G32_SFLOAT = 103,
    R32G32B32_UINT = 104,
    R32G32B32_SINT = 105,
    R32G32B32_SFLOAT = 106,
    R32G32B32A32_UINT = 107,
    R32G32B32A32_SINT = 108,
    R32G32B32A32_SFLOAT = 109,
    R64_UINT = 110,
    R64_SINT = 111,
    R64_SFLOAT = 112,
    R64G64_UINT = 113,
    R64G64_SINT = 114,
    R64G64_SFLOAT = 115,
    R64G64B64_UINT = 116,
    R64G64B64_SINT = 117,
    R64G64B64_SFLOAT = 118,
    R64G64B64A64_UINT = 119,
    R64G64B64A64_SINT = 120,
    R64G64B64A64_SFLOAT = 121,
    B10G11R11_UFLOAT_PACK32 = 122,
    E5B9G9R9_UFLOAT_PACK32 = 123,
    D16_UNORM = 124,
    X8_D24_UNORM_PACK32 = 125,
    D32_SFLOAT = 126,
    S8_UINT = 127,
    D16_UNORM_S8_UINT = 128,
    D24_UNORM_S8_UINT = 129,
    D32_SFLOAT_S8_UINT = 130,
    BC1_RGB_UNORM_BLOCK = 131,
    BC1_RGB_SRGB_BLOCK = 132,
    BC1_RGBA_UNORM_BLOCK = 133,
    BC1_RGBA_SRGB_BLOCK = 134,
    BC2_UNORM_BLOCK = 135,
    BC2_SRGB_BLOCK = 136,
    BC3_UNORM_BLOCK = 137,
    BC3_SRGB_BLOCK = 138,
    BC4_UNORM_BLOCK = 139,
    BC4_SNORM_BLOCK = 140,
    BC5_UNORM_BLOCK = 141,
    BC5_SNORM_BLOCK = 142,
    BC6H_UFLOAT_BLOCK = 143,
    BC6H_SFLOAT_BLOCK = 144,
    BC7_UNORM_BLOCK = 145,
    BC7_SRGB_BLOCK = 146,
    ETC2_R8G8B8_UNORM_BLOCK = 147,
    ETC2_R8G8B8_SRGB_BLOCK = 148,
    ETC2_R8G8B8A1_UNORM_BLOCK = 149,
    ETC2_R8G8B8A1_SRGB_BLOCK = 150,
    ETC2_R8G8B8A8_UNORM_BLOCK = 151,
    ETC2_R8G8B8A8_SRGB_BLOCK = 152,
    EAC_R11_UNORM_BLOCK = 153,
    EAC_R11_SNORM_BLOCK = 154,
    EAC_R11G11_UNORM_BLOCK = 155,
    EAC_R11G11_SNORM_BLOCK = 156,
    ASTC_4x4_UNORM_BLOCK = 157,
    ASTC_4x4_SRGB_BLOCK = 158,
    ASTC_5x4_UNORM_BLOCK = 159,
    ASTC_5x4_SRGB_BLOCK = 160,
    ASTC_5x5_UNORM_BLOCK = 161,
    ASTC_5x5_SRGB_BLOCK = 162,
    ASTC_6x5_UNORM_BLOCK = 163,
    ASTC_6x5_SRGB_BLOCK = 164,
    ASTC_6x6_UNORM_BLOCK = 165,
    ASTC_6x6_SRGB_BLOCK = 166,
    ASTC_8x5_UNORM_BLOCK = 167,
    ASTC_8x5_SRGB_BLOCK = 168,
    ASTC_8x6_UNORM_BLOCK = 169,
    ASTC_8x6_SRGB_BLOCK = 170,
    ASTC_8x8_UNORM_BLOCK = 171,
    ASTC_8x8_SRGB_BLOCK = 172,
    ASTC_10x5_UNORM_BLOCK = 173,
    ASTC_10x5_SRGB_BLOCK = 174,
    ASTC_10x6_UNORM_BLOCK = 175,
    ASTC_10x6_SRGB_BLOCK = 176,
    ASTC_10x8_UNORM_BLOCK = 177,
    ASTC_10x8_SRGB_BLOCK = 178,
    ASTC_10x10_UNORM_BLOCK = 179,
    ASTC_10x10_SRGB_BLOCK = 180,
    ASTC_12x10_UNORM_BLOCK = 181,
    ASTC_12x10_SRGB_BLOCK = 182,
    ASTC_12x12_UNORM_BLOCK = 183,
    ASTC_12x12_SRGB_BLOCK = 184,
    G8B8G8R8_422_UNORM = 1000156000,
    B8G8R8G8_422_UNORM = 1000156001,
    G8_B8_R8_3PLANE_420_UNORM = 1000156002,
    G8_B8R8_2PLANE_420_UNORM = 1000156003,
    G8_B8_R8_3PLANE_422_UNORM = 1000156004,
    G8_B8R8_2PLANE_422_UNORM = 1000156005,
    G8_B8_R8_3PLANE_444_UNORM = 1000156006,
    R10X6_UNORM_PACK16 = 1000156007,
    R10X6G10X6_UNORM_2PACK16 = 1000156008,
    R10X6G10X6B10X6A10X6_UNORM_4PACK16 = 1000156009,
    G10X6B10X6G10X6R10X6_422_UNORM_4PACK16 = 1000156010,
    B10X6G10X6R10X6G10X6_422_UNORM_4PACK16 = 1000156011,
    G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16 = 1000156012,
    G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16 = 1000156013,
    G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16 = 1000156014,
    G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16 = 1000156015,
    G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16 = 1000156016,
    R12X4_UNORM_PACK16 = 1000156017,
    R12X4G12X4_UNORM_2PACK16 = 1000156018,
    R12X4G12X4B12X4A12X4_UNORM_4PACK16 = 1000156019,
    G12X4B12X4G12X4R12X4_422_UNORM_4PACK16 = 1000156020,
    B12X4G12X4R12X4G12X4_422_UNORM_4PACK16 = 1000156021,
    G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16 = 1000156022,
    G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16 = 1000156023,
    G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16 = 1000156024,
    G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16 = 1000156025,
    G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16 = 1000156026,
    G16B16G16R16_422_UNORM = 1000156027,
    B16G16R16G16_422_UNORM = 1000156028,
    G16_B16_R16_3PLANE_420_UNORM = 1000156029,
    G16_B16R16_2PLANE_420_UNORM = 1000156030,
    G16_B16_R16_3PLANE_422_UNORM = 1000156031,
    G16_B16R16_2PLANE_422_UNORM = 1000156032,
    G16_B16_R16_3PLANE_444_UNORM = 1000156033,
    PVRTC1_2BPP_UNORM_BLOCK_IMG = 1000054000,
    PVRTC1_4BPP_UNORM_BLOCK_IMG = 1000054001,
    PVRTC2_2BPP_UNORM_BLOCK_IMG = 1000054002,
    PVRTC2_4BPP_UNORM_BLOCK_IMG = 1000054003,
    PVRTC1_2BPP_SRGB_BLOCK_IMG = 1000054004,
    PVRTC1_4BPP_SRGB_BLOCK_IMG = 1000054005,
    PVRTC2_2BPP_SRGB_BLOCK_IMG = 1000054006,
    PVRTC2_4BPP_SRGB_BLOCK_IMG = 1000054007,
    ASTC_4x4_SFLOAT_BLOCK_EXT = 1000066000,
    ASTC_5x4_SFLOAT_BLOCK_EXT = 1000066001,
    ASTC_5x5_SFLOAT_BLOCK_EXT = 1000066002,
    ASTC_6x5_SFLOAT_BLOCK_EXT = 1000066003,
    ASTC_6x6_SFLOAT_BLOCK_EXT = 1000066004,
    ASTC_8x5_SFLOAT_BLOCK_EXT = 1000066005,
    ASTC_8x6_SFLOAT_BLOCK_EXT = 1000066006,
    ASTC_8x8_SFLOAT_BLOCK_EXT = 1000066007,
    ASTC_10x5_SFLOAT_BLOCK_EXT = 1000066008,
    ASTC_10x6_SFLOAT_BLOCK_EXT = 1000066009,
    ASTC_10x8_SFLOAT_BLOCK_EXT = 1000066010,
    ASTC_10x10_SFLOAT_BLOCK_EXT = 1000066011,
    ASTC_12x10_SFLOAT_BLOCK_EXT = 1000066012,
    ASTC_12x12_SFLOAT_BLOCK_EXT = 1000066013,
    G8_B8R8_2PLANE_444_UNORM_EXT = 1000330000,
    G10X6_B10X6R10X6_2PLANE_444_UNORM_3PACK16_EXT = 1000330001,
    G12X4_B12X4R12X4_2PLANE_444_UNORM_3PACK16_EXT = 1000330002,
    G16_B16R16_2PLANE_444_UNORM_EXT = 1000330003,
    A4R4G4B4_UNORM_PACK16_EXT = 1000340000,
    A4B4G4R4_UNORM_PACK16_EXT = 1000340001,
    MAX_ENUM = 0x7FFFFFFF
};

enum class SurfaceTransformFlagBits {
    IdentityBit = 0x00000001,
    Rotate90Bit = 0x00000002,
    Rotate180Bit = 0x00000004,
    Rotate270Bit = 0x00000008,
    HorizontalMirrorBit = 0x00000010,
    HorizontalMirrorRotate90Bit = 0x00000020,
    HorizontalMirrorRotate180Bit = 0x00000040,
    HorizontalMirrorRotate270Bit = 0x00000080,
    InheritBit = 0x00000100,
    MaxEnum = 0x7fffffff
};
using SurfaceTransformFlags = Flags;

enum class CompositeAlphaFlagBits {
    OpaqueBit = 0x00000001,
    PreMultipliedBit = 0x00000002,
    PostMultipliedBit = 0x00000004,
    InheritBit = 0x00000008,
    MaxEnum = 0x7FFFFFFF
};
using CompositeAlphaFlags = Flags;

enum class TextureUsageFlagBits {
    TransferSrcBit = 0x00000001,
    TransferDstBit = 0x00000002,
    SampledBit = 0x00000004,
    StorageBit = 0x00000008,
    ColorAttachmentBit = 0x00000010,
    DepthStencilAttachmentBit = 0x00000020,
    TransientAttachmentBit = 0x00000040,
    InputAttachmentBit = 0x00000080,
    VideoDecodeDstBit = 0x00000400,
    VideoDecodeSrcBit = 0x00000800,
    VideoDecodeDpbBit = 0x00001000,
    FragmentDensityMapBit = 0x00000200,
    FragmentShadingRateAttachmentBit = 0x00000100,
    VideoEncodeDstBit = 0x00002000,
    VideoEncodeSrcBit = 0x00004000,
    VideoEncodeDpbBit = 0x00008000,
    InvocationMaskBit = 0x00040000,
    MaxEnum = 0x7fffffff
};
using TextureUsageFlags = Flags;

enum class TextureTiling {
    Optimal = 0,
    Linear = 1,
    DrmFormatModifier = 1000158000,
    MaxEnum = 0x7fffffff
};

enum class TextureLayout {
    Undefined = 0,
    General = 1,
    ColorAttachmentOptimal = 2,
    DepthStencilAttachmentOptimal = 3,
    DepthStencilReadOnlyOptimal = 4,
    ShaderReadOnlyOptimal = 5,
    TransferSrcOptimal = 6,
    TransferDstOptimal = 7,
    Preinitialized = 8,
    DepthReadOnlyStencilAttachmentOptimal = 1000117000,
    DepthAttachmentStencilReadOnlyOptimal = 1000117001,
    DepthAttachmentOptimal = 1000241000,
    DepthReadOnlyOptimal = 1000241001,
    StencilAttachmentOptimal = 1000241002,
    StencilReadOnlyOptimal = 1000241003,
    PresentSrc = 1000001002,
    VideoDecodeDst = 1000024000,
    VideoDecodeSrc = 1000024001,
    VideoDecodeDpb = 1000024002,
    SharedPresent = 1000111000,
    FragmentDensityMapOptimal = 1000218000,
    FragmentShadingRateAttachmentOptimal = 1000164003,
    VideoEncodeDst = 1000299000,
    VideoEncodeSrc = 1000299001,
    VideoEncodeDpb = 1000299002,
    ReadOnlyOptimal = 1000314000,
    AttachmentOptimal = 1000314001,
    MaxEnum = 0x7fffffff
};

enum class SharingMode {
    Exclusive = 0,
    Concurrent = 1,
    MaxEnum = 0x7FFFFFFF
};

enum class TextureType {
    TextureType1D = 0,
    TextureType2D = 1,
    TextureType3D = 2,
    MaxEnum = 0x7fffffff
};

enum class ViewType {
    ViewType1D = 0,
    ViewType2D = 1,
    ViewType3D = 2,
    ViewTypeCube = 3,
    ViewType1DArray = 4,
    ViewType2DArray = 5,
    ViewTypeCubeArray = 6,
    MaxEnum = 0x7fffffff
};

enum class TextureAspectFlagBits {
    None = 0,
    ColorBit = 0x00000001,
    DepthBit = 0x00000002,
    StencilBit = 0x00000004,
    MetadataBit = 0x00000008,
    Plane0Bit = 0x00000010,
    Plane1Bit = 0x00000020,
    Plane2Bit = 0x00000040,
    MemoryPlane0Bit = 0x00000080,
    MemoryPlane1Bit = 0x00000100,
    MemoryPlane2Bit = 0x00000200,
    MemoryPlane3Bit = 0x00000400,
    MaxEnum = 0x7fffffff
};
using TextureAspectFlags = Flags;

struct TextureSubresourceRange {
    TextureAspectFlags aspectMask{ static_cast<uint32_t>(TextureAspectFlagBits::ColorBit) };
    uint32_t baseMipLevel{ 0 };
    uint32_t levelCount{ remainingMipLevels };
    uint32_t baseArrayLayer{ 0 };
    uint32_t layerCount{ remainingArrayLayers };
};

enum class BufferUsageFlagBits {
    TransferSrcBit = 0x00000001,
    TransferDstBit = 0x00000002,
    UniformTexelBufferBit = 0x00000004,
    StorageTexelBuffer_bit = 0x00000008,
    UniformBufferBit = 0x00000010,
    StorageBufferBit = 0x00000020,
    IndexBufferBit = 0x00000040,
    VertexBufferBit = 0x00000080,
    IndirectBufferBit = 0x00000100,
    ShaderDeviceAddressBit = 0x00020000,
    VideoDecodeSrcBit = 0x00002000,
    VideoDecodeDstBit = 0x00004000,
    TransformFeedbackBufferBit = 0x00000800,
    TransformFeedbackCounterBufferBit = 0x00001000,
    ConditionalRenderingBit = 0x00000200,
    AccelerationStructureBuildInputReadOnlyBit = 0x00080000,
    AccelerationStructureStorageBit = 0x00100000,
    ShaderBindingTableBit = 0x00000400,
    VideoEncodeDstBit = 0x00008000,
    VideoEncodeSrcBit = 0x00010000,
    SamplerDescriptorBufferBit = 0x00200000,
    ResourceDescriptorBufferBit = 0x00400000,
    PushDescriptorsDescriptorBufferBit = 0x04000000,
    MicromapBuildInputReadOnlyBit = 0x00800000,
    MicromapStorageBit = 0x01000000,
    MaxEnum = 0x7fffffff
};
using BufferUsageFlags = Flags;

enum class MemoryUsage {
    Unknown = 0,
    GpuOnly = 1,
    CpuOnly = 2,
    CpuToGpu = 3,
    GpuToCpu = 4,
    CpuCopy = 5,
    GpuLazilyAllocated = 6,
    MaxEnum = 0x7fffffff
};

enum class ShaderStageFlagBits {
    VertexBit = 0x00000001,
    TessellationControlBit = 0x00000002,
    TessellationEvaluationBit = 0x00000004,
    GeometryBit = 0x00000008,
    FragmentBit = 0x00000010,
    ComputeBit = 0x00000020,
    AllGraphics = 0x0000001f,
    All = 0x7fffffff,
    RaygenBit = 0x00000100,
    AnyHitBit = 0x00000200,
    ClosestHitBit = 0x00000400,
    MissBit = 0x00000800,
    IntersectionBit = 0x00001000,
    CallableBit = 0x00002000,
    TaskBit = 0x00000040,
    MeshBit = 0x00000080,
    MaxEnum = 0x7fffffff
};
using ShaderStageFlags = Flags;

enum class ResourceBindingType {
    Sampler = 0,
    CombinedImageSampler = 1,
    SampledImage = 2,
    StorageImage = 3,
    UniformTexelBuffer = 4,
    StorageTexelBuffer = 5,
    UniformBuffer = 6,
    StorageBuffer = 7,
    DynamicUniformBuffer = 8,
    DynamicStorageBuffer = 9,
    InputAttachment = 10,
    MaxEnum = 0x7fffffff
};

enum class PrimitiveTopology {
    PointList = 0,
    LineList = 1,
    LineStrip = 2,
    TriangleList = 3,
    TriangleStrip = 4,
    TriangleFan = 5,
    LineListWithAdjacency = 6,
    LineStripWithAdjacency = 7,
    TriangleListWithAdjacency = 8,
    TriangleStripWithAdjacency = 9,
    PatchList = 10,
    MaxEnum = 0x7fffffff
};

enum class CullModeFlagBits {
    None = 0,
    FrontBit = 0x00000001,
    BackBit = 0x00000002,
    FrontAndBack = 0x00000003,
    MaxEnum = 0x7fffffff
};
using CullModeFlags = Flags;

enum class FrontFace {
    CounterClockwise = 0,
    Clockwise = 1,
    MaxEnum = 0x7fffffff
};

enum class PolygonMode {
    Fill = 0,
    Line = 1,
    Point = 2,
    MaxEnum = 0x7fffffff
};

} // namespace ToyRenderer