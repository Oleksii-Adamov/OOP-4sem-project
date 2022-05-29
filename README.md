# OOP-4sem-project
## Naming convensions: https://google.github.io/styleguide/cppguide.html#Naming
## Реалізовані паттерни (1):
### Builder
## TO DO (General):
### 1. Клієнт-серверна архітектура.
### 2. Графічний інтерфейс для учня.
### 3. Графічний інтерфейс для викладача.
### 4. Механізм надсилання завдань викладачем (у відповідний час).
### 5. Відправка завдань з програмування, автоматична перевірка їх за допомогою тестів, які викладач завчасно створює.
### 6. Відправка довільних завдань та відповідей, у вигляді довільних файлів (можна додати обмеження на формат файлу, який може виставити викладач).
### 7. Можливість повертати бали та коментарі учню.
### 8. Перевірка завдань з програмування викладачем, для кожного завдання можна побачити запропоновану оцінку з тестів, які тести не пройшли, код.
### 9. Відправка завдань з математики. Файл з повним рішенням (або прямо у інтерфейсі текст, але тут потрібно морочитись з формулами), та введені відповіді у поля.
### 10. Перевірка завдань з математики. Автоматична перевірка відповіді для деяких типів завдань за допомогою зовнішніх сервісів (напр. Wolfram). 
### 11. Генерація завдань з математики.
### 12. Генерація звітів успішності групи учнів.
### 13. Чат між групою учнів та викладачем (Не обов'язково).
### 14. Створення завдань у форматі тестів.
### 15. Можливість виділяти помилки.

## Вимоги до лаби:
### 1. Необхідно підготувати документацію реалізованої програми. Зокрема, треба описати заплановану архітектуру програми (використовуючи текстові описи та/або UML діаграми). Також має бути опис того, як використовувати можливості програми – як через графічний інтерфейс, так і з коду. 
### 2. Юніт тести функціональності (логіки), без БД, GUI, тощо.
### 3. Необхідно реалізувати документацію коду (наприклад, з використанням Doxygen).
### 4. Додатково до коду необхідно описати використання патернів в документації – тобто які саме патерни використано, де в коді (точні посилання, якщо використано в декількох місцях – на усі використання), чому використано ці патерни, які проблеми вони вирішують, переваги та недоліки використання цих патернів в цих місцях тощо. Варто також проаналізувати реалізовану програму з точки зору дотримання принципів архітектури, проектування та розробки.
### 5. 10-12 патернів.
## Ідеї для паттернів.
### Abstract Factory / Factory Method - для різних завдань
### Singleton - аутенфікація і/або налаштування
### Proxy - аутенфікація при деяких зверненнях до серверу (наприклад видалення групи)
### Adapter - для адаптації інтерфейсу Wolfram і/або ASIO.
### 