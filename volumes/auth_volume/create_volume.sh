SCRIPTPATH="$( cd "$(dirname "$0")" ; pwd -P )"
docker volume rm --force test-db-pumpwood-auth-conncected
docker volume create --name test-db-pumpwood-auth-conncected --opt type=none --opt device=$SCRIPTPATH/data/ --opt o=bind
