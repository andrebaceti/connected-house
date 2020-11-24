source version
git add --all
git commit -m "Building a new version for RabbitMQ MQTT enable ${VERSION}"
git tag -a mqtt_${VERSION} -m "Building a new version for RabbitMQ MQTT enable ${VERSION}"
git push
git push origin mqtt_${VERSION}

docker push andrebaceti/rabbitmq-mqtt:$VERSION
