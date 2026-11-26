// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class MyFooGameTarget : TargetRules
{
	public MyFooGameTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		//ExtraModuleNames.Add("MyFooGame");
		ExtraModuleNames.AddRange( new string[] 
		{
            "MyFooGame"

			//-- My Modules --
            , "MyCore"
			, "MyRender"
			, "MyUI"
			//-- My Modules Test --
			, "MyTest"
			
			//-- My PLugins --
			, "FooBar"
        });
	}
}
