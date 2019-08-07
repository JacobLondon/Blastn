# 
# Build the Docker container to run the implementations with all dependencies.
# 
# Puts all files for the project under `/root`
# 
# For building:
#   docker build -t pyblastn .
# 

FROM ubuntu:18.04

# prepare installation of dependencies
RUN apt-get update
RUN apt-get install -y --no-install-recommends \
    git python3 python3-pip gcc make \
    vim wget

# ensure proper ssl certificate for git
RUN apt-get install -y --reinstall --no-install-recommends ca-certificates 
RUN mkdir /usr/local/share/ca-certificates/cacert.org
RUN wget -P /usr/local/share/ca-certificates/cacert.org http://www.cacert.org/certs/root.crt http://www.cacert.org/certs/class3.crt
RUN update-ca-certificates
RUN git config --global http.sslCAinfo /etc/ssl/certs/ca-certificates.crt

# get repository
WORKDIR /root

RUN git clone https://github.com/JacobLondon/SeniorProject.git

# done
CMD ["/bin/bash"]
