#!/bin/bash

cd ../Plugins/FMODStudio
git ls-files | tr '\n' ' ' | xargs git update-index --no-assume-unchanged
