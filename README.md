# Command-Line Media Browser and Player

## Introduction
This project is a Linux-based command-line application designed for managing and playing audio and video media files. It offers users the ability to browse media, manage playlists, view and edit metadata, and control media playback. Additionally, it integrates with external hardware through the S32K144 board for enhanced control features.

---

## Key Features

### **Basic Functionalities**

#### **1. Application Behavior:**
- The program can be executed from any directory on the system, allowing users to operate it from their preferred location.
- It supports running from external USB devices, provided the device is mounted and files are accessible for parsing.

#### **2. Available Features:**

1. **Browsing Media Files:**
   - Users can view a list of media files (both audio and video) from the current directory and its subdirectories.
   - Pagination is available, displaying 25 files per page.

2. **Playlist Management:**
   - Users can list available playlists and view or modify specific playlists.
   - Options to create, update, or delete playlists are included.

3. **Metadata Management (via Taglib):**
   - Media metadata can be viewed and edited directly from either the media list or specific playlists.
   - For audio files, displayed metadata includes track name, album, artist, genre, publisher, and year of release.
   - Video files display properties such as name, size, duration, bitrate, and codec information.
   - Users can modify existing metadata or add new metadata fields.

4. **Music Playback (via SDL2 Library):**
   - Basic media controls are available, including:
     - Play/Pause
     - Skip to Next/Previous Track
   - After one track finishes, the application automatically moves to the next.
   - Playback information such as the current time and total duration is shown during playback.

5. **Volume Control:**
   - Users can adjust the device’s volume directly through the application.

---

### **External Device Integration**

#### **1. S32K144 Board Integration:**
- The S32K144 board facilitates volume control via its onboard ADC.
- It allows playback control through physical buttons, enabling users to play, pause, stop, or skip music.
- Information about the current song is displayed on the board’s screen.

#### **2. Deliverables:**

1. **Software Requirements Document:**
   - Descriptions of use cases.
   - Detailed workflow charts.

2. **Design Documentation:**
   - **Architecture Design:** Follows the Model-View-Controller (MVC) design pattern.
   - **Detailed Design:** Breakdown of components and module-level descriptions.

3. **Code & Testing:**
   - Full implementation of the application.
   - Unit tests for each component to ensure functionality.

---

## Libraries Installation

### **FTXUI Installation**

FTXUI is a C++ library that enables the creation of text-based user interfaces for CLI applications. Follow these steps to set up FTXUI for your project.

#### 1. Clone the FTXUI Repository

Use Git to clone the repository from GitHub:

```bash
git clone https://github.com/ArthurSonzogni/FTXUI.git

