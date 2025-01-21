# Software Requirements Specification

## 1. Introduction

### 1.1. Purpose

This document specifies the requirements for a command-line interface (CLI) application designed for Linux to browse, manage, and play media files (audio and video). This application will provide basic media player functionalities and advanced metadata handling capabilities.

### 1.2. Project Scope

This document covers all functionalities of the CLI media browser and player application, including:

- Browsing local and external (USB) media files.
- Managing and interacting with playlists.
- Viewing and editing media file metadata.
- Playing audio files using the SDL2 library.
- Controlling playback and volume via the CLI and a connected S32K144 board.
- Platform: Linux-based systems.

### 1.3. Definitions, Acronyms, and Abbreviations

- **CLI:** Command-Line Interface
- **USB:** Universal Serial Bus
- **SDL2:** Simple DirectMedia Layer 2
- **ADC:** Analog-to-Digital Converter
- **SRS:** Software Requirements Specification
- **Metadata:** Data that provides information about other data.
- **Taglib:** A C++ library for reading and editing the metadata of several popular audio and video formats.
- **S32K144:** A specific microcontroller board from NXP Semiconductors.

### 1.4. References

- SDL2 Documentation: [https://www.libsdl.org/](https://www.libsdl.org/)
- Taglib Documentation: [https://taglib.org/](https://taglib.org/)
- S32K144 Documentation: [https://www.nxp.com/docs/en/data-sheet/S32K1xx.pdf](https://www.nxp.com/docs/en/data-sheet/S32K1xx.pdf)

## 2. Overall Description

### 2.1. Product Perspective

The application will be a standalone CLI program running on Linux. It will interact directly with the file system and the SDL2 library for audio playback. Interaction with external USB devices will require mounting the device within the Linux environment. The application will also communicate with the S32K144 board via a defined protocol (details to be determined).

### 2.2. User Classes and Characteristics

The primary user of this application will be individuals comfortable using the command line interface in a Linux environment. They are expected to have basic knowledge of file systems and media file formats. Users may range from hobbyists to developers who need a simple media management tool.

### 2.3. Operating Environment

- **Operating System:** Linux (various distributions)
- **Compiler:** GCC or Clang (supporting C++11 or higher)
- **Libraries:** SDL2, Taglib, Standard C/C++ libraries, Serial communication library (for S32K144 interaction)
- **Hardware:** Standard PC hardware capable of running the specified operating system and libraries.

### 2.4. Design and Implementation Constraints

- The application must be developed using C/C++.
- Audio playback must be implemented using the SDL2 library in a separate thread.
- Metadata handling must be implemented using the Taglib library.
- External USB devices must be mounted and unmounted programmatically.

### 2.5. User Documentation

Basic user documentation will be provided in the form of a README file or man page. This documentation will include:

- Installation instructions.
- Instructions on how to run the application.
- A description of available commands and options.
- Examples of common usage scenarios.

## 3. Functional Requirements

### 3.1. Application Execution

- Must run from any directory on the system.
- Detect and mount external USB devices, parsing media files within them.

### 3.2. Media File Management

- Display a paginated list (25 items per page) of media files, including all subfolders.
- Supported audio file types: MP3.
- Supported video file types: MP4.

### 3.3. Playlist Management

- Display all available playlists.
- View the content of a specific playlist.
- Create, update, or delete playlists.

### 3.4. Metadata Handling (Main Feature)

- View metadata for media files.
  - **Audio Metadata:** Track Name, Album, Artist, Duration, Genre, Publisher, Publish Year, etc.
  - **Video Metadata:** Name, Size, Duration, Bitrate, Codec.
- Edit metadata:
  - Change existing values.
  - Add new metadata keys/values.
  - Available from either media list or a playlist view.

### 3.5. Media Playback

- Play audio using SDL2 in a separate thread.
- Controls:
  - Play/Pause.
  - Next/Previous track.
  - Automatic track advancement when a song finishes.
- Display playback information (current time and duration).
- Adjust device volume.

### 3.6. Hardware Integration

**S32K144 Board Features:**

- Control playback using buttons:
  - Play/Pause.
  - Stop.
  - Next/Previous track.
- Display current song details (e.g., Title, Artist) on the board's screen.
- Adjust volume using the ADC on the S32K144 board.

---
