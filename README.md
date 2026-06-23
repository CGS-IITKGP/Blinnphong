<div id="top"></div>

<!-- PROJECT SHIELDS -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links-->
<div align="center">

[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]

</div>

<!-- PROJECT LOGO -->
<br />
<div align="center">

# Blinn–Phong Lighting with OpenGL + ImGui

### Interactive Real-Time Lighting Control for Imported Blender 3D Models

</div>
<details>
<summary>Table of Contents</summary>

- [About The Project](#about-the-project)
- [Getting Started](#getting-started)
  - [Installation](#installation)
- [Usage](#usage)
- [Contact](#contact)
  - [Maintainer(s)](#maintainers)
  - [Creator(s)](#creators)
- [Additional Documentation](#additional-documentation)

</details>

## About The Project

<div align="center">

<table>
<tr>
<td width="50%">
<img src="https://github.com/Jasz-rgb/Blinnphong/blob/a64d8525145e06a34187373f46dd776053fe49dc/Screenshot%202025-08-10%20234838.png"
     alt="Lighting Preview"
     width="100%">
</td>

<td width="50%">
<img src="https://github.com/Jasz-rgb/Blinnphong/blob/a64d8525145e06a34187373f46dd776053fe49dc/Screenshot%202025-08-10%20232840.png"
     alt="Scene Preview"
     width="90%">
</td>
</tr>
</table>

</div>

This project demonstrates a real-time implementation of the **Blinn–Phong lighting model** using **OpenGL**, featuring an interactive **ImGui-based editor** for modifying lighting parameters and scene settings at runtime. The application supports imported Blender assets through Assimp and provides a configurable environment for experimenting with different light types, attenuation models, and material properties.


### ✨ Key Features
* Real-time **Blinn–Phong shading**
* Interactive **ImGui control panel**
* Directional, Point, and Spot Lights
* Runtime adjustment of:
  * Ambient, Diffuse, and Specular components
  * Light attenuation parameters
  * Spotlight cutoff angles
* Multiple imported Blender scenes and models
* Camera navigation with keyboard and mouse controls
* OpenGL rendering pipeline using GLSL shaders
* Assimp-powered model loading and texture support
* Easily extensible architecture for advanced lighting and shading techniques

<p align="right">(<a href="#top">back to top</a>)</p>

# Technologies & Frameworks

### Core Technologies

![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge\&logo=cplusplus\&logoColor=white)
![OpenGL](https://img.shields.io/badge/OpenGL-5586A4?style=for-the-badge\&logo=opengl\&logoColor=white)
![GLSL](https://img.shields.io/badge/GLSL-4B4B4B?style=for-the-badge\&logo=opengl\&logoColor=white)

### Graphics Libraries

![GLFW](https://img.shields.io/badge/GLFW-000000?style=for-the-badge\&logo=glfw\&logoColor=white)
![GLAD](https://img.shields.io/badge/GLAD-FFB13B?style=for-the-badge\&logo=opengl\&logoColor=black)
![GLM](https://img.shields.io/badge/GLM-8B0000?style=for-the-badge\&logo=cplusplus\&logoColor=white)

### UI & Tooling

![ImGui](https://img.shields.io/badge/ImGui-4A90E2?style=for-the-badge\&logo=cplusplus\&logoColor=white)
![Visual Studio](https://img.shields.io/badge/Visual%20Studio%202022-5C2D91?style=for-the-badge&logo=microsoft&logoColor=white)
![vcpkg](https://img.shields.io/badge/vcpkg-0078D7?style=for-the-badge\&logo=microsoft\&logoColor=white)

### Asset & Model Pipeline

![Assimp](https://img.shields.io/badge/Assimp-FF6F00?style=for-the-badge\&logo=cplusplus\&logoColor=white)
![stb\_image](https://img.shields.io/badge/stb__image-6C757D?style=for-the-badge\&logo=image\&logoColor=white)
![Blender](https://img.shields.io/badge/Blender-E87D0D?style=for-the-badge\&logo=blender\&logoColor=white)

### Build System

![CMake](https://img.shields.io/badge/CMake-064F8C?style=for-the-badge\&logo=cmake\&logoColor=white)

## Project Structure

```text
Blinnphong/
│
├── assets/
│   ├── Scene1/
│   ├── Scene2/
|
├── shaders/
│   ├── vertex_shader.glsl
│   ├── fragment_shader.glsl
|
├── src/
│   ├── main.cpp
│   ├── shader.cpp
│   ├── ...other .cpp files
│   └── glad.c
|
├── include/
│   ├── shader.h
│   ├── ...other .h files
|
├── external/
│   ├── glad/
│   ├── KHR/
│   └── imgui/
|
├── Blinnphong.sln
├── Blinnphong.vcxproj
├── Blinnphong.vcxproj.filters
├── CMakeLists.txt
├── README.md

```

<p align="right">(<a href="#top">back to top</a>)</p>

## Getting Started

This project uses **OpenGL**, **GLFW**, **GLM**, **Assimp**, **GLAD**, and **ImGui**.

### Prerequisites

* Visual Studio 2022
* Git

### Installation

1. **Clone the repository**

```bash
git clone https://github.com/CGS-IITKGP/Blinnphong.git
```

2. **Install vcpkg**

Open PowerShell:

```powershell
git clone https://github.com/microsoft/vcpkg
cd vcpkg
.\bootstrap-vcpkg.bat
```

3. **Install project dependencies**

```powershell
.\vcpkg install glm:x64-windows
.\vcpkg install glfw3:x64-windows
.\vcpkg install assimp:x64-windows
```

4. **Integrate vcpkg with Visual Studio**

```powershell
.\vcpkg integrate install
```

5. **Open the project**

Open:

```text
Blinnphong.sln
```

using Visual Studio 2022.

6. **Build and Run**

Select:

```text
Debug | x64
```

or

```text
Release | x64
```

and run the project.

### Dependencies Included in Repository

The following libraries are already bundled with the project:

* GLAD
* ImGui
* stb_image

The following libraries are installed through vcpkg:

* GLFW
* GLM
* Assimp

<p align="right">(<a href="#top">back to top</a>)</p>

## Usage

Once the project is running:

### Camera Controls

| Key | Action |
|------|---------|
| **W** | Move Forward |
| **A** | Move Left |
| **S** | Move Backward |
| **D** | Move Right |
| **E** | Move Down |
| **Q** | Move Up |
| **F5** | Toggle ImGui Control Panel |
| **Mouse** | Look Around |
| **Scroll Wheel** | Zoom In/Out |

### ImGui Controls

The editor panel allows runtime modification of:

* Directional Light Properties
* Point Light Properties
* Spot Light Properties
* Ambient, Diffuse, and Specular Components
* Light Colors
* Light Direction
* Light Position
* Attenuation Parameters
* Spotlight Cutoff Angles

### Scene Interaction

* Explore multiple imported Blender scenes
* Observe real-time lighting changes on different materials
* Compare the visual impact of directional, point, and spot lighting
* Experiment with attenuation and spotlight behavior

<div align="center">
  <a href="https://github.com/CGS-IITKGP/Blinnphong">
    <img width="40%" alt="image" src="https://github.com/CGS-IITKGP/Blinnphong/blob/dfbc74495e7caf232fdde55ebeffdabd9906af4b/Screenshot%202025-08-10%20231154.png">
  </a>
  <a href="https://github.com/CGS-IITKGP/Blinnphong">
    <img width="40%" alt="image" src="https://github.com/Jasz-rgb/Blinnphong/blob/a64d8525145e06a34187373f46dd776053fe49dc/Screenshot%202025-08-10%20231232.png">
  </a>
  <a href="https://github.com/CGS-IITKGP/Blinnphong">
    <img width="40%" alt="image" src="https://github.com/user-attachments/assets/057c5812-7790-4663-bd84-a142406beba1">
  </a>
  <a href="https://github.com/CGS-IITKGP/Blinnphong">
    <img width="40%" alt="image" src="https://github.com/user-attachments/assets/18585260-2a82-4e0b-80c7-b00e8d43c98e">
  </a>
</div>
<p align="right">(<a href="#top">back to top</a>)</p>

## Contact

### Maintainer(s)

The currently active maintainer(s) of this project.

<!-- UPDATE -->
- [Jasmine](https://github.com/Jasz-rgb)

### Creator(s)

Honoring the original creator(s) and ideator(s) of this project.

<!-- UPDATE -->
- [Jasmine](https://github.com/Jasz-rgb)

<p align="right">(<a href="#top">back to top</a>)</p>

## Additional documentation

  - [License](/LICENSE)

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- MARKDOWN LINKS & IMAGES -->

[contributors-shield]: https://img.shields.io/github/contributors/Jasz-rgb/Blinnphong.svg?style=for-the-badge
[contributors-url]: https://github.com/Jasz-rgb/Blinnphong/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/Jasz-rgb/Blinnphong.svg?style=for-the-badge
[forks-url]: https://github.com/Jasz-rgb/Blinnphong/network/members
[stars-shield]: https://img.shields.io/github/stars/Jasz-rgb/Blinnphong.svg?style=for-the-badge
[stars-url]: https://github.com/Jasz-rgb/Blinnphong/stargazers
[issues-shield]: https://img.shields.io/github/issues/Jasz-rgb/Blinnphong.svg?style=for-the-badge
[issues-url]: https://github.com/Jasz-rgb/Blinnphong/issues
[license-shield]: https://img.shields.io/github/license/Jasz-rgb/Blinnphong.svg?style=for-the-badge
[license-url]: https://github.com/Jasz-rgb/Blinnphong/blob/master/LICENSE
