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
git clone --branch=gh-pages ${REMOTE_REPO} gh-pages && \
cd gh-pages && \
if [ -d "${GH_PAGES_SUBDIR}" ]; then
  git rm -rf ${GH_PAGES_SUBDIR}
fi && \
mkdir ${GH_PAGES_SUBDIR} && \
cp -Rf ${GITHUB_WORKSPACE}/${BUILD_DIR}/* ${GH_PAGES_SUBDIR} && \
git config user.name "${GITHUB_ACTOR}" && \
git config user.email "${GITHUB_ACTOR}@users.noreply.github.com" && \
git add -f . && \
if [ -z "$(git status --porcelain)" ]; then
    echo "Nothing to commit" && \
    exit 0
fi && \
git commit -m 'Deploy to GitHub Pages' && \
git push -fq origin gh-pages && \
rm -fr .git && \
cd $GITHUB_WORKSPACE && \
echo "Content of $BUILD_DIR has been deployed to GitHub Pages."
