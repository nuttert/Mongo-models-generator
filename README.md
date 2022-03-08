# Mongo models generator with slave

## How to run
`docker-compose up -d //Run mongo` 

`docker-compose exec mongo-master /scripts/rs-init.sh // Initialize mongo`

`docker-compose run test` # Run test container

At the test container:

`./generators/generate.sh` // generete models, configs, collections

`make run  // build and run project`

At second terminal:

`docker-compose exec mongo-master mongo`

At the mongo console:

`dbrs:PRIMARY> use main` // switch to main db

`dbrs:PRIMARY> db.createCollection("categories")` // create test collections "categories"

`dbrs:PRIMARY> db.categories.insertOne({"id": NumberLong(2), "name": "abc"});` // Insert test object to the collection and watch to the first console
