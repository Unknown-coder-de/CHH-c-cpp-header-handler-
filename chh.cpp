// our goal is to create a command handler for headers.
// hence, its name will be chh, which is likely similar to '.cpp' and '.h'.

// it requires some macros for shorting the lengthy code.

#define for_n(n, i) for (std::size_t i = 0; i < n; i++)

// some standard headers for further use.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>

// collection of functions for playing with files, folder or drive.

namespace drive
{
  std::string fetch(const std::string &filepath) noexcept
  {
    std::string file_content = "";
    std::ifstream file(filepath);

    if (file.is_open())
    {
      std::string line;
      while (std::getline(file, line))
        file_content += line + "\n";
      file.close();
    }

    return file_content;
  }
  // extends the file data with content.
  void write(const std::string &filepath, const std::string &content) noexcept
  {
    std::ofstream file(filepath);
    if (file.is_open())
      file << content, file.close();
  }

  inline void delete_file(const std::string &filepath) noexcept { std::remove(filepath.c_str()); }
  inline void delete_folder(const std::string &folder_path) noexcept
  {
    std::filesystem::remove_all(folder_path);
  }

  // removes the file's data, then write the new content.
  inline void overwrite(const std::string &filepath, const std::string &content) noexcept
  {
    delete_file(filepath), write(filepath, content);
  }
  // replaces file with new file and delete the data of the pre-file.
  inline void replace(const std::string &file_with, const std::string &new_file) noexcept
  {
    delete_file(file_with), write(file_with, drive::fetch(new_file));
  }
  // exchanges two files with each other.
  void exchange(const std::string &file1, const std::string &file2) noexcept
  {
    std::string content1 = drive::fetch(file1), content2 = drive::fetch(file2);
    drive::overwrite(file1, content2), drive::overwrite(file2, content1);
  }

  // polishes the path by removing chars like '"', '<', '>', '?', '|', ':' and '*'.
  std::string path_strip(const std::string &path) noexcept
  {
    std::string new_path(path);
    std::size_t j = 0;
    for_n(path.length(), i) if (path[i] != '\"' and path[i] != ':' and path[i] != '*' and path[i] != '<' and path[i] != '>' and path[i] != '|' and path[i] != '?' and path[i] != '\n')
        new_path[j++] = path[i];
    new_path[j] = '\0';
    return new_path;
  }

  namespace list
  {
    // lists the paths of files in the directory and don't looks inside the sub-dirs.
    std::vector<std::string> files(const std::string &in_dir) noexcept
    {
      std::vector<std::string> file_paths;
      for (const auto &entry : std::filesystem::directory_iterator(in_dir))
        if (entry.is_regular_file())
          file_paths.push_back(entry.path().string());
      return file_paths;
    }
    // lists the paths of all files in the directory irrespective of sub-dirs.
    std::vector<std::string> all_files(const std::string &in_dir) noexcept
    {
      std::vector<std::string> file_paths;
      for (const auto &entry : std::filesystem::recursive_directory_iterator(in_dir))
        if (entry.is_regular_file())
          file_paths.push_back(entry.path().string());
      return file_paths;
    }
    // lists the paths of folders in the directory and don't looks inside the sub-dirs.
    std::vector<std::string> folders(const std::string &in_dir) noexcept
    {
      std::vector<std::string> folder_paths;
      for (const auto &entry : std::filesystem::directory_iterator(in_dir))
        if (entry.is_directory())
          folder_paths.push_back(entry.path().string());
      return folder_paths;
    }
    // lists the paths of all folders in the directory irrespective of sub-dirs.
    std::vector<std::string> all_folders(const std::string &in_dir) noexcept
    {
      std::vector<std::string> folder_paths;
      for (const auto &entry : std::filesystem::recursive_directory_iterator(in_dir))
        if (entry.is_directory())
          folder_paths.push_back(entry.path().string());
      return folder_paths;
    }
  }

  namespace exist
  {
    inline bool file(const std::string &filepath) noexcept
    {
      if (std::ifstream(filepath).is_open())
        return true;
      return false;
    }
    inline bool folder(const std::string &folder_path) noexcept
    {
      return std::filesystem::is_directory(folder_path);
    }
    // returns the no. of files in the path.
    inline std::size_t file_in(const std::string &path) noexcept
    {
      std::size_t count = 0;
      for (const auto &entry : std::filesystem::recursive_directory_iterator(path))
        if (entry.is_regular_file())
          count++;
      return count;
    }
    // returns the no. of folders in the path.
    inline std::size_t folder_in(const std::string &path) noexcept
    {
      std::size_t count = 0;
      for (const auto &entry : std::filesystem::recursive_directory_iterator(path))
        if (entry.is_directory())
          count++;
      return count;
    }
  }
}

// natural language tool kit for attending input arguments.

namespace nltk
{
  std::vector<std::string> tokenize(const std::string &input) noexcept
  {
    std::vector<std::string> tokens;
    std::istringstream iss(input);
    std::string token;
    while (iss >> token)
      tokens.push_back(token);
    return tokens;
  }
  std::string to_string(const int argn, const char *argc[]) noexcept
  {
    std::string result;
    for_n(argn, i)
    {
      result += argc[i];
      if (i < argn - 1)
        result += ' ';
    }
    return result;
  }
  std::vector<std::string> to_strings(const int argn, const char *argc[]) noexcept
  {
    std::vector<std::string> result;
    for (std::size_t i = 1; i < argn; i++)
      result.push_back(argc[i]);
    return result;
  }

  namespace extract
  {
    inline std::string filename(const std::string &filepath) noexcept
    {
      return std::filesystem::path(filepath).filename().string();
    }
    inline std::string file_ext(const std::string &filepath) noexcept
    {
      return std::filesystem::path(filepath).extension().string();
    }
  }
}

// a include directory which will be loaded or update automatically on runtime.

std::string include_dr;

// headers related functions for organizing the code.

void update_header(const std::string header_path) noexcept
{
  std::cout << "fetching..\r";
  std::string content = drive::fetch(header_path);
  std::cout << "analysis..\r";
  std::string path_to_write = ::include_dr + '/' + nltk::extract::filename(header_path);
  std::cout << "writing.\r";
  drive::overwrite(path_to_write, content);
  std::cout << "header updated successfully.\n";
}
void update_library(const std::string folder_path) noexcept
{
  std::vector<std::string> files_to_copy = drive::list::all_files(folder_path);

  for (const std::string &file_path : files_to_copy)
  {
    std::string file_name = nltk::extract::filename(file_path),
                destination_path = ::include_dr + '/' + file_name;
    drive::write(destination_path, drive::fetch(file_path));
  }

  std::cout << "library updated successfully.\n";
}

// our main program goes here..
// starts by taking arguments, i.e., argn(no. of args) and argc(arguments tokens).

int main(const int argn, const char *argc[]) noexcept
{
  // first of all, the include directory will be loaded.

  ::include_dr = drive::path_strip(drive::fetch("./include.path"));
  ::include_dr.pop_back();

  // arguments are converted to standard c++ style data.

  std::vector<std::string> args = nltk::to_strings(argn, argc);

  // a while loop to attend commands rapidly if multiple time in a single line.

  if (args[0] == "update" or args[0] == "-u")
  {
    if (drive::exist::file(args[1]))
      update_header(args[1]);
    if (drive::exist::folder(args[1]))
      update_library(args[1]);
  }
  else if (args[0] == "replace" or args[0] == "-r")
  {
    std::string pre_file = ::include_dr + '/' + args[1];
    if (drive::exist::file(pre_file) and drive::exist::file(args[2]))
      drive::delete_file(pre_file), update_header(args[2]);
    if (drive::exist::folder(pre_file) and drive::exist::folder(args[2]))
      drive::delete_folder(pre_file), update_library(args[2]);
  }
  else if (args[0] == "delete" or args[0] == "-d")
  {
    std::string path = ::include_dr + '/' + args[1];
    if (drive::exist::file(path))
      drive::delete_file(path);
    if (drive::exist::folder(path))
      drive::delete_folder(path);
  }
  else if (args[0] == "help" or args[0] == "-h")
  {
    if (args[1] == "update" or args[1] == "-u")
      std::cout << "update : this command is used to update or create or send a header to include directory.\n\nits syntax is as follows:\n-> chh update 'path/to/header' .\nor you can also use it as:\n-> chh -u 'path/to/header' .\n";
    else if (args[1] == "replace" or args[1] == "-r")
      std::cout << "replace : this command is used to replace a header existing in include directory with another header whom path you had given.\n\nits syntax is as follows:\n-> chh replace 'name_header.c/cpp' 'path/to/new_header' .\n or you can also use it as:\n-> chh -r 'name_of_header.c/cpp' 'path/to/new_header' .\n";
    else if (args[1] == "delete" or args[1] == "-d")
      std::cout << "delete : this command is used to delete a header existing in include directory.\n\nits syntax is as follows:\n-> chh delete 'header_name.c/cpp' .\nor you can also use it as:\n-> chh -d 'header_name.c/cpp'\n";
    else if (args[1] == "help" or args[1] == "-h")
      std::cout << "help : this command is used to know about the commands of header command handling.\n\nits syntax is as follows:\n-> chh help <your desire command or blank could be left> .\nor you can also use it as:\n-> chh -h <your desire command or blank could be left>\n";
    else
      std::cout << "this is CHH(command handler for headers). this allows c/c++ programmers to use their own headers and libraries as standard headers and libraries of c/c++.\n\nupdate : this command is used to update or create or send a header to include directory.\nreplace : this command is used to replace a header existing in include directory with another header whom path you had given.\ndelete : this command is used to delete a header existing in include directory.\nhelp : this command is used to know about the commands of header command handling.\n\nnote: keep a space gap between each token.";
  }
  else
    std::cout << "invalid token '" << args[0] << "'\n";

  return 0;
}
