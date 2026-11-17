# Sem10 — сигналы

Исходные материалы — из [материалов семинара Миши Филитова для группы 238](https://github.com/lll-phill-lll/hse_caos/tree/master/2024_238/19-signal). Ссылка из описания [записи «АКОС 19. Сигналы»](https://www.youtube.com/watch?v=VQsQKi8Dig0) ведёт на старый адрес папки.

| В записи | Пример | Что посмотреть |
|---|---|---|
| [0:00](https://www.youtube.com/watch?v=VQsQKi8Dig0) | `01_yess.c` | `Ctrl+C`, `Ctrl+Z`, `jobs`, `fg`, `bg`. |
| [25:16](https://www.youtube.com/watch?v=VQsQKi8Dig0&t=1516s) | `02_sigaction.c` | Действие по умолчанию, игнорирование и свой обработчик. |
| [42:12](https://www.youtube.com/watch?v=VQsQKi8Dig0&t=2532s) | `03_signal_race.c` | Упрощённый пример: обработчик меняет одну переменную, а `main` затирает изменение. |
| [48:15](https://www.youtube.com/watch?v=VQsQKi8Dig0&t=2895s) | `04_atomic.c` | Флаг `volatile sig_atomic_t`; второй `Ctrl+C` завершает программу. |
| [53:15](https://www.youtube.com/watch?v=VQsQKi8Dig0&t=3195s) | `05_block_sigint.c` | `sigprocmask`: доставка сигнала откладывается, пока он заблокирован. |
| [1:05:00](https://www.youtube.com/watch?v=VQsQKi8Dig0&t=3900s) | `06_siginfo.c` | `SA_SIGINFO`: получить PID и UID отправителя. Для демонстрации отправь `kill -INT PID` из другого терминала. |

## Запуск в Linux

```bash
bin=$(mktemp -d)
for src in *.c; do
    gcc -std=gnu17 -O0 -g "$src" -o "$bin/${src%.c}" || break
done
"$bin/01_yess" 1 hello
```

Большинство примеров ждут сигнал или работают в цикле. Для ограниченного запуска можно использовать, например, `timeout 5s "$bin/01_yess" 1 hello`. Это демонстрационный код: не копируй `printf` из обработчика `06_siginfo.c` в рабочие программы, а при написании своего `sigaction` инициализируй всю структуру, включая `sa_mask`.

В `03_signal_race.c` `main` читает `counter` и ждёт до пяти секунд перед записью. После `main read: 0` нажми `Ctrl+C`: обработчик запишет `100`, а `main` затрёт его, записав `0 + 1` на основе старого чтения. Если сигнал не посылать, перед записью счётчик останется равен `0`. `sleep(5)` только расширяет окно для демонстрации, а `sig_atomic_t` не делает весь инкремент атомарным.

```bash
gcc -g 03_signal_race.c -o /tmp/sem10-race
/tmp/sem10-race
```

Лекции в дополнение к записи: [сигналы, часть 1](https://www.youtube.com/watch?v=krl9nVDUmsI), [сигналы, часть 2](https://www.youtube.com/watch?v=ET2nOVjTfH8), [IPC](https://www.youtube.com/watch?v=Hd1RYV113V0).

## Дополнение: signalfd

[`07_signalfd.c`](07_signalfd.c) — отдельный пример для Linux, не из записи. Вместо обработчика блокируем `SIGUSR1` обычной маской процесса и читаем сведения о сигнале из файлового дескриптора. В программе `read()` ждёт сигнал, а после него возвращает запись `signalfd_siginfo` с номером сигнала и PID отправителя.

Первый терминал, из каталога семинара:

```bash
gcc -Wall -Wextra 07_signalfd.c -o /tmp/sem10-signalfd
/tmp/sem10-signalfd
```

Второй терминал: подставь PID из вывода программы.

```bash
kill -USR1 PID
```

В отличие от `sigaction`, здесь нет асинхронного обработчика: печатаем результат обычным `printf` после `read()`. Такой fd можно ждать вместе с другими дескрипторами через `poll` или `epoll`. Обычный `SIGUSR1` по-прежнему не образует очередь: несколько отправок могут слиться в одну. [Справка signalfd(2)](https://man7.org/linux/man-pages/man2/signalfd.2.html).
