import os
import ycm_core
# from clang_helpers import PrepareClangFlags

flags = [
    '-Wall',
    '-Wextra',
    '-Werror',
    '-isystem',
    '-Wno-long-long',
    '-Wno-variadic-macros',
    '-fexceptions',
    '-ferror-limit=10000',
    '-DNDEBUG',
    '-std=c++17',
    '-x',
    'c++',
    # '-xc++',
    # '-xc',
    "-fPIE",
    '-I/usr/lib/',
    '/usr/include',
    '/usr/local/include',
    '-DQT_CORE_LIB',
    '-DQT_GUI_LIB',
    '-DQT_NETWORK_LIB',
    '-DQT_QML_LIB',
    '-DQT_QUICK_LIB',
    '-DQT_SQL_LIB',
    '-DQT_WIDGETS_LIB',
    '-DQT_XML_LIB',
    '-I./includes/',
    '-I./tests/googletest/googletest/include',
    '-I./tests/',
    '-I./tests/includes',
    '-I/usr/lib/',
    '-I/usr/lib/qt/mkspecs/linux-clang'
]

compilation_database_folder = ''

if os.path.exists( compilation_database_folder ):
  database = ycm_core.CompilationDatabase( compilation_database_folder )
else:
  database = None

SOURCE_EXTENSIONS = [ '.cpp', '.cxx', '.cc', '.c', '.m', '.mm']

def DirectoryOfThisScript():
  return os.path.dirname( os.path.abspath( __file__ ) )

def IsHeaderFile( filename ):
  extension = os.path.splitext( filename )[ 1 ]
  return extension in [ '.h', '.hxx', '.hpp', '.hh' ]

def GetCompilationInfoForFile( filename ):
  if IsHeaderFile( filename ):
    basename = os.path.splitext( filename )[ 0 ]
    for extension in SOURCE_EXTENSIONS:
      replacement_file = basename + extension
      if os.path.exists( replacement_file ):
        compilation_info = database.GetCompilationInfoForFile(
          replacement_file )
        if compilation_info.compiler_flags_:
          return compilation_info
    return None
  return database.GetCompilationInfoForFile( filename )

def Settings( **kwargs ):
  if not database:
    return {
      'flags': flags,
      'include_paths_relative_to_dir': DirectoryOfThisScript()
    }
  filename = kwargs[ 'filename' ]
  compilation_info = GetCompilationInfoForFile( filename )
  if not compilation_info:
    return None

  return {
    'flags': list( compilation_info.compiler_flags_ ),
    'include_paths_relative_to_dir': compilation_info.compiler_working_dir_
  }
