import random
import string

my_set = set()

# for i in range(500):
#     # Сгенерировать случайную длину строки от 1 до 10 символов
#     length = random.randint(1, 10)
#     # Сгенерировать случайную строку заданной длины
#     stri = ''.join(random.choices(string.ascii_lowercase + string.ascii_uppercase + string.digits, k=length))
#     my_set.add(stri)
#     # Вывести строку на экран
#     print(stri, sep=' ', end=' ')
# print("\n",len(my_set))

my_set = list(map(int, input().split()))

sorted(my_set)

print(my_set)

