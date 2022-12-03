import pytchat
chat = pytchat.create(video_id="id")
print("started listening!")
while chat.is_alive():
    
    for c in chat.get().sync_items():
        print(f"{c.datetime} [{c.author.name}]- {c.message}")
        user = c.author.name
        time = c.datetime
        message = c.message

        if message == "red":
            print("USER: ", user, "SAID RED")
