# CHH-c-cpp-header-handler-
# Overview
CHH is a basic-featured command-line tool crafted for C/C++ programmers to streamline the management and organization of their headers and libraries. It enables users to treat their custom headers and libraries as standard ones, simplifying the inclusion process in their projects.

# Features
Update Header: Rapidly update or create a header in the include directory.
Update Library: Enhance the library by updating or adding files from a specified folder.
Replace Header: Swap an existing header in the include directory with a new one.
Delete Header: Remove a header from the include directory.
Help Command: Obtain information about the available commands and their usage.
# Installation
Clone the repository: git clone https://github.com/unknown-coder-de/CHH.git
Compile the code using your preferred C++ compiler.
Configure the include directory path by creating a file named include.path with the path inside.
Usage
# Update Header
```
chh update 'path/to/header'
```
or

```
chh -u 'path/to/header'
```
This command swiftly updates or creates a header in the include directory.

# Update Library
```
chh update 'path/to/folder'
```
This command enhances the library by adding or updating files from the specified folder.

# Replace Header
```
chh replace 'name_header.c/cpp' 'path/to/new_header'
```
or

```
chh -r 'name_of_header.c/cpp' 'path/to/new_header'
```
This command replaces an existing header with a new one in the include directory.

# Delete Header
```
chh delete 'header_name.c/cpp'
```
or

```
chh -d 'header_name.c/cpp'
```
This command deletes a header from the include directory.

# Help Command
```
chh help <your_desired_command>
```
or

```
chh -h <your_desired_command>
```
This command provides information about the available commands and their usage.

# Note
Ensure to maintain a space gap between each token when entering commands.

# Contributing
Feel free to contribute to the development of CHH by submitting issues or pull requests.

# License
This project is licensed under the MIT License.

Experience the simplicity of CHH, your go-to basic-featured header handler for C/C++! 🚀
