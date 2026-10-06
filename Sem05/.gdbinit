set disassembly-flavor intel

python
import gdb

if "_refresh_tui_before_prompt" in globals():
    gdb.events.before_prompt.disconnect(_refresh_tui_before_prompt)

def _refresh_tui_before_prompt():
    try:
        windows = gdb.execute("info win", to_string=True)
        if any(row.split()[:1] == ["cmd"] for row in windows.splitlines()):
            gdb.execute("refresh")
    except gdb.error:
        pass

gdb.events.before_prompt.connect(_refresh_tui_before_prompt)
end
