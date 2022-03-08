# Mongo models generator with slave

## How to run
`docker-compose up -d #Run mongo` 

![image](https://user-images.githubusercontent.com/35408275/157297389-1a0308c8-2bff-4c27-81ff-05e49aa473cf.png)


`docker-compose exec mongo-master /scripts/rs-init.sh # Initialize mongo`

![image](https://user-images.githubusercontent.com/35408275/157297459-82614700-7b06-43d8-a46a-5ce658b8f98d.png)


`docker-compose run test # Run test container` 

![image](https://user-images.githubusercontent.com/35408275/157297505-0bf87d0c-5ff0-4fda-b2b5-d455d601df9d.png)


At the test container:

`./generators/generate.sh # generete models, configs, collections` 

![image](https://user-images.githubusercontent.com/35408275/157297586-a20636eb-cc9a-4ec5-88fe-1861a83fef46.png)

`make run  // build and run project`

At second terminal:

`docker-compose exec mongo-master mongo`

At the mongo console:

`dbrs:PRIMARY> use main # switch to main db` 

`dbrs:PRIMARY> db.createCollection("categories") # create test collections "categories"` 

`dbrs:PRIMARY> db.categories.insertOne({"id": NumberLong(2), "name": "abc"}); #// Insert test object to the collection` 
