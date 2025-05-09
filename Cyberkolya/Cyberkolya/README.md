# Киберколя

Вы попали на работу в паблик с мемами. От предыдущего программиста вам досталась база данных в формате tsv и система мемоучёта Киберколя℠. Беда в том, что предыдущий админ знал только про динамический массив и сортировку.
Всё было хорошо, пока паблик с мемами не превратился в медиаимперию. Нагрузка на Киберколю возросла. Предыдущий админ выгорел от попыток улучшения своего кода и уволился.
Вам повезло, перед уходом программист реализовал тесты и, хотя не знал структуры данных, обложился абстракциями.

Ваша задача: реализовать новый, быстрый вариант базы данных, унаследовавшись от AbstractDatabase. LegacyDatabase оставьте для сравнения.

В базе данных хранятся посты и пользователи.
У поста хранятся:
- Id      - int, id поста на стене (уникален только в рамках одной стены).
- OwnerId - int, id стены поста (группы или пользователя).
- FromId  - int, id автора поста.
- Date    - int, дата и время создания поста в формате unixtime.
- Likes   - int, количество лайков. Может уменьшаться или увеличиваться.
- Reposts - int, количество репостов. Может только увеличиваться.

У пользователя хранятся:
- Id        - int, id пользователя или группы
- FirstName - string, имя пользователя или название группы
- LastName  - string, фамилия пользователя или тип группы

Поддерживаемые виды запросов:
- Добавление пользователя
- Получение пользователя по id
- Добавление поста
- Получение поста по id и ownerId
- Удаление поста
- Добавление лайка к посту
- Удаление лайка из поста
- Добавление репоста к посту
- Подсчёт ТОП-k постов на стене за заданный период времени по лайкам.
- Подсчёт ТОП-k постов на стене за заданный период времени по репостам.
- Подсчёт ТОП-k авторов на стене за заданный период времени по лайкам.
- Подсчёт ТОП-k авторов на стене за заданный период времени по репостам.



При выборе контейнеров обратите внимание на условия инвалидации итераторов: https://en.cppreference.com/w/cpp/container.