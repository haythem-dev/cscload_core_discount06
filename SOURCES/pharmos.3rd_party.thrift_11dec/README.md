# thrift

## Build process

### Windows

1. Execute `ant retrieve`.

2. Execute `/proc/prepare.bat`. This copies the Thrift sources from "ext" folder into the project and also the patch files from /patch/lib.

3. Execute `/proc/build.bat`. This builds the Thrift library.
(Do not rely on IDE build (Ctrl+Shift+B) as tit does not take into account all necessary dependencies!)

### AIX

1. Execute `ant retrieve`.

2. Execute `/proc/prepare.bat`. This copies the Thrift sources from "ext" folder into the project and also the patch files from /patch/lib.

3. Execute `/proc/build.sh`. This builds the Thrift library.

## Thrift version upgrade

1. Download the latest Thrift sources and compiler from the [official Thrift website](https://thrift.apache.org/).

2. Pack and deploy it to `NEXUS genesis / org/apache/thrift_source`
(Therefor you can use ant with /build/sources/build.xml & ivy.xml)

3. Update Thrift version in `/build/ivy.xml`:
>`<dependency org="org.apache" name="thrift_source" rev="0.12.0" conf="win64+compile->*">`

4. Execute `ant retrieve`.

5. Execute `/proc/prepare.bat`.

6. Update files in project folder /thrift acording to files of project \thrift-*\lib\cpp\libthrift.vcxproj

7. Execute IDE build (`Ctrl+Shift+B`) and check if headers in `/patch/vs_required_headers` are sufficient or still required.

## Rollout Process

### Build artifacts

1. Merge feature branch into develop

### Deploy artifacts
