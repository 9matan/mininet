include(ExternalProject)
set(mininet_LIBRARIES "")

# Find Eigen.
find_package( Eigen3 REQUIRED )
include_directories(SYSTEM ${EIGEN3_INCLUDE_DIR})
list(APPEND mininet_LIBRARIES ${EIGEN3_LIBRARIES})

# Find Google-gflags.
option(DOWNLOAD_GFLAGS "Download gflags from git" ON)
if(DOWNLOAD_GFLAGS)
  include("cmake/External/gflags.cmake")
else(DOWNLOAD_GFLAGS)
  include("cmake/Modules/FindGflags.cmake")
endif(DOWNLOAD_GFLAGS)
include_directories(SYSTEM ${GFLAGS_INCLUDE_DIRS})
list(APPEND mininet_LIBRARIES ${GFLAGS_LIBRARIES})

# Find Google-glog.
option(DOWNLOAD_GLOG "Download glog from git" ON)
if(DOWNLOAD_GLOG)
  include("cmake/External/glog.cmake")
else(DOWNLOAD_GLOG)
  include("cmake/Modules/FindGlog.cmake")
endif(DOWNLOAD_GLOG)
include_directories(SYSTEM ${GLOG_INCLUDE_DIRS})
list(APPEND mininet_LIBRARIES ${GLOG_LIBRARIES})
