using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraWorkScript : MonoBehaviour 
{
	public PlayerScript player;
	
	// Update is called once per frame
	void Update () 
	{
		if (!player.GetIsCollisionWall())
		{
			transform.localPosition += new Vector3(player.GetPlayerTransformX() / 4, 0, 0);
		}
		transform.position += new Vector3(0, 0, 1.50f);
	}
}
