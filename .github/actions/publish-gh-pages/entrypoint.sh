#!/bin/sh

set -e

echo "#################################################"
echo "Changing directory to 'BUILD_DIR' $BUILD_DIR ..."
cd $BUILD_DIR

echo "#################################################"
echo "Now deploying to GitHub Pages..."
REMOTE_REPO="https://${GH_PAT}@github.com/${GITHUB_REPOSITORY}.git" && \
REPONAME="$(echo $GITHUB_REPOSITORY| cut -d'/' -f 2)" && \
OWNER="$(echo $GITHUB_REPOSITORY| cut -d'/' -f 1)" && \
REMOTE_BRANCH="gh-pages" && \
TMP_DIR="$(mktemp -d)" && \
cd ${TMP_DIR} && \
git clone --branch=gh-pages ${REMOTE_REPO} && \
git rm -rf ${GH_PAGES_SUBDIR} && \
cp -Rf ${BUILD_DIR} ${GH_PAGES_SUBDIR} && \
git add -f . && \
git commit -m 'Deploy to GitHub Pages' && \
git push -fq origin gh-pages && \
rm -fr .git && \
cd $GITHUB_WORKSPACE && \
echo "Content of $BUILD_DIR has been deployed to GitHub Pages."
