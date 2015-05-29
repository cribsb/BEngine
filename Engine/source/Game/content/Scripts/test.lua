player = {
    pos = {
    x = 0, y = 10, z = 0,
    },
    filename = "Content\\Models\\RunningSoldier.dae",
    animationindex = 0
}

function Initialize()

end

function Update(d)
    if keyPressed("w") == 1 then
        player.pos.z = player.pos.z + 10*d
    end
    if keyPressed("s") == 1 then
        player.pos.z = player.pos.z - 10*d
    end
    if keyPressed("a") == 1 then
        player.pos.x = player.pos.x + 10*d
    end
    if keyPressed("d") == 1 then
        player.pos.x = player.pos.x - 10*d
    end
    --write(player.pos.y)
end