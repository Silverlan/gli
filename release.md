## Project Health

| Service | System | Compiler | Status |
| ------- | ------ | -------- | ------ |
| [Drone](https://drone.io/github.com/g-truc/gli) | Linux 64 bits | GCC 4.6.3 | [![Build Status](https://drone.io/github.com/g-truc/gli/status.png)](https://drone.io/github.com/g-truc/gli/latest) |

## [Lastest release](https://github.com/g-truc/gli/releases/latest)

## Release notes

#### [GLI 0.8.0.0](https://github.com/g-truc/gli/releases/latest) - 2015-XX-XX
- Added texture swizzle support
- Added support for load and store
- Added support for many new formats
- Added KMG support and spec proposal
- Added texture memory swizzle support
- Added generate_mipmaps for uncompressed formats
- Added sampler 1D, 2D and 3D
- Added sampler texel fetch and texel write
- Added texture lod
- Added sampler clear
- Reordered formats
- Fixed PVRTC2 support
- Fixed luminance and alpha translation to OpenGL #56
- Fixed DXGI_FORMAT_B8G8R8X8_UNORM_SRGB support #59
- Fixed FORMAT_RGBA8_UNORM DDS loading using DDPF_RGBA mode #60
- Fixed handling of DDS DDPF_ALPHAPIXELS #68

#### [GLI 0.7.0.0](https://github.com/g-truc/gli/releases/tag/0.7.0.0) - 2015-09-01
- Added KTX loading and saving
- Added gli::load for generic file loading, either DDS or KTX files depending on filename extensions
- Added gli::save for generic file saving, either DDS or KTX files depending on filename extensions
- Added texture views using different texture format, including compressed texture formats
- Added fine granularity includes
- Improved API documentation
- Much faster texture comparisons is non optimal cases. (Measured ~21x faster on Intel IVB)
- Explicitly handling of texture targets: fixed various cases of cubemap and texture arrays failing to load with DDS
- Fixed GCC build
- Fixed warnings
- Fixed saved DDS header size on #52

#### [GLI 0.6.1.1](https://github.com/g-truc/gli/releases/tag/0.6.1.1) - 2015-07-18
- Updated API documentation
- Fixed link error

#### [GLI 0.6.1.0](https://github.com/g-truc/gli/releases/tag/0.6.1.0) - 2015-07-18
- Fixed interface inconsistencies
- Improved clear(), data() and size() performance using caching
- Removed internal dependence to std::fstream
- Added FORMAT_BGRX8_UNORM and FORMAT_BGRX8_SRGB support #48, #43
- Improved FORMAT_RGB8_UNORM loading

#### [GLI 0.6.0.0](https://github.com/g-truc/gli/releases/tag/0.6.0.0) - 2015-06-28
- Large refactoring
- Added loading DDS from memory
- Added saving DDS to memory
- Improved DDS coverage for R, RG, RGB and RGBA formats
- Added DDS ASTC, PVRTC, ATC and ETC support
- Added DDS alpha, luminance and alpha luminance support
- Added PVRTC2, ETC2 and EAC formats

#### [GLI 0.5.1.1](https://github.com/g-truc/gli/releases/tag/0.5.1.1) - 2014-01-20
- Fixed swizzled RGB channel when reading back a DDS
- Fixed getMask* link error

#### [GLI 0.5.1.0](https://github.com/g-truc/gli/releases/tag/0.5.1.0) - 2014-01-18
- Added flip function
- Added level_count function
- Fixed interaction with std::map (#33)
- Added texelFetch and texelWrite functions

#### [GLI 0.5.0.0](https://github.com/g-truc/gli/releases/tag/0.5.0.0) - 2013-11-24
- Essencially a rewrite of the library
- Added explicit copies
- Added single memory allocation per texture storage
- Added texture views
- Added texture copies
- Added comparison operators
- Added clear

#### GLI 0.4.1.0: 2013-03-10
- Added DDS saving
- Fixed GCC build
- Fixed XCode build

#### GLI 0.4.0.0: 2013-01-28
- Large API refactoring
- Performance improvements at loading: 50x in debug and 50% in release build
- Added texture2DArray
- Added textureCube and textureCubeArray
- Added texture3D
- Added texture1D and texture1DArray
- Improved DDS loading support

#### GLI 0.3.0.3: 2011-04-05
- Fixed bugs

#### GLI 0.3.0.2: 2011-02-08
- Fixed bugs

#### GLI 0.3.0.1: 2010-10-15
- Fixed bugs

#### GLI 0.3.0.0: 2010-10-01
- Added DDS10 load and store (BC1 - BC7)
- Added extension system
- Added automatic OpenGL texture object creation from file

#### GLI 0.2.2.0: 2010-09-07
- Added DDS exporter

#### GLI 0.2.1.1: 2010-05-12
- Fixed GCC build

#### GLI 0.2.1.0: 2010-02-15
- Added texelWrite function
- Fixed Visual Studio 2010 warnings
- Added readme.txt and copying.txt

#### GLI 0.2.0.0: 2010-01-10
- Updated API
- Removed Boost dependency

#### GLI 0.1.1.0: 2009-09-18
- Fixed DDS loader
- Added RGB8 to DDS loader
- Added component swizzle operation
- Added 32 bits integer components support
- Fixed texel fetch

#### GLI 0.1.0.0: 2009-03-28
- Added TGA loader
- Added DDS loader
- Added duplicate, crop, partial copy
- Added mipmaps generation.