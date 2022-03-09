# Mongo models generator with slave

## About

Основные компоненты проекта:
- Генератор конфигов
- Генератор моделей для MongoDB с поддержкой сериализации/десереализации
- Генератор коллекций для MongoDB с поддержкой загрузки всех коллекций и их дальнейшей актуализации через `mongo change streams`
- `Mongo Manager`, слушающий change stream и отправляющий события(`insert, update ,delete`) в соответствующий объект класса коллекции.
- Менеджер конфигов, через который можно получить любой конфиг

Дополнительно:
- Обертка на rapidjson
- Пример yaml схем(конфигов, моделей/коллекций) и json конфиг для mongodb

## Как обновить существующую коллекцию?

Для добавления/удаления/изменения полей коллекции достаточно поменять схему в `models/schemas`(перед этим стоит удалить из билда эту коллекцию и её модели).

## Как добавить новую коллекцию?

Для добавления новой коллекции необходимо добавить её в models/schemas и в конструктор менеджера `databases/mongodb/manager.cc`(перед этим стоит удалить из билда configs-list).

## Как обновить существующий конфиг?

Для добавления/удаления/изменения полей коллекции достаточно поменять схему в `configs/schemas`(перед этим стоит удалить из билда этот конфиг и его модели).

## Как добавить новый конфиг?

Для добавления нового конфига необходимо добавить его в models/schemas(перед этим стоит удалить из билда configs-list).

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

`dbrs:PRIMARY> db.categories.insertOne({"id": NumberLong(2), "name": "abc"}); # Insert test object to the collection` 
