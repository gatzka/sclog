FROM alpine:3.10

LABEL "maintainer"="Stephan Gatzka<stephan.gatzka@gmail.com>"
LABEL "repository"="http://github.com/gatzka/ghaction-deploy-ghpages"
LABEL "homepage"="http://github.com/gatzka/ghaction-deploy-ghpages"

LABEL "com.github.actions.name"="GitHub Pages Deploy"
LABEL "com.github.actions.description"="Deploy static assets to GitHub Pages."
LABEL "com.github.actions.icon"="upload-cloud"
LABEL "com.github.actions.color"="blue"

COPY entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh

RUN apk update && apk upgrade && apk add git

ENTRYPOINT ["/entrypoint.sh"]
