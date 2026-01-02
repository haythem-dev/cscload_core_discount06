#!/bin/sh
set -ex

# Remove old directories and files
rm -rf ./codedocu
rm -rf doxy_warn.txt

# Create necessary directories
mkdir ./codedocu
mkdir ./codedocu/internal
mkdir ./codedocu/customer

# Define variables
DOXYGEN=$DEVLIB_PATH/marathon/bin/doxygen/doxygen
HOST="10.156.63.91"
USERNAME="ftp.outbound"
PRIVATE_KEY="/software/home/$USER/.ssh/id_rsa_ftp_outbound"

# Run doxygen
$DOXYGEN -d Preprocessor Doxyfile.internal
$DOXYGEN -d Preprocessor Doxyfile.customer

# Check if the private key file exists
if [ ! -f "$PRIVATE_KEY" ]; then
  echo "Warning: Private key file $PRIVATE_KEY not accessible!"
  exit 1
fi

# Execute the SFTP command using the specified private key
sftp -i $PRIVATE_KEY $USERNAME@$HOST <<END_SCRIPT
cd csc_core_applications/changelog
lcd codedocu/internal/html
put index.html
put pages.html
put versionoverview.html
put versionhistory.html
cd ../customer
lcd ../../customer/html
put index.html
bye
END_SCRIPT

exit 0
