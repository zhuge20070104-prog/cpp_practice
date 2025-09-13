#!/bin/bash
# Build Image 
docker build -t parse_path:latest .

# Build
docker run -d --name cpp_build -v /home/fredric/code/cpp_practice/cppweb:/usr/src/cppweb -ti cppbox:latest bash
docker exec -ti cpp_build bash

# Run
docker run -v /home/fredric/code/cpp_practice/cppweb/:/usr/src/cppweb -p 8080:8080 -e PORT=8080 parse_path:latest
