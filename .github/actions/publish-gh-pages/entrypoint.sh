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
git init && \
git config user.name "${GITHUB_ACTOR}" && \
git config user.email "${GITHUB_ACTOR}@users.noreply.github.com" && \
pwd && \
echo ${REMOTE_REPO} && \
git clone --branch=gh-pages ${REMOTE_REPO} gh-pages && \
echo "here 1" && \
cd gh-pages && \
if [ -d "${GH_PAGES_SUBDIR}" ]; then
  git rm -rf ${GH_PAGES_SUBDIR}
fi && \
mkdir ${GH_PAGES_SUBDIR} && \
cp -Rf ${GITHUB_WORKSPACE}/${BUILD_DIR} ${GH_PAGES_SUBDIR} && \
echo "here 2" && \
git add -f . && \
git commit -m 'Deploy to GitHub Pages' && \
echo "here 3" && \
git push -fq origin gh-pages && \
rm -fr .git && \
echo "here 4" && \
cd $GITHUB_WORKSPACE && \
echo "Content of $BUILD_DIR has been deployed to GitHub Pages."
