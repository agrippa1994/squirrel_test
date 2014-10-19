function debugPrint(text)
{
	print("[SQUIRREL] " + text);
}

function main(){
	local instance = Player(5.5, 34.5, 345.5);
	
	instance.positionChangedCallback = function(x, y, z)
	{
		debugPrint("New position: " + x + " " + y + " " + z);
	};
	
	instance.x = 5.5;
	instance.setPosition(123.0, 11345.5, 34566.6);
	debugPrint(instance.y);

	instance.releasePositionChangedCallback();
};

main();
