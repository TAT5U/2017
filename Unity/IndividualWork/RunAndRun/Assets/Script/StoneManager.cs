using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StoneManager : MonoBehaviour 
{
	public GameObject player_;

	public GameObject stone_;

	[SerializeField]private float createDelayS_;

	private void Awake()
	{
		StartCoroutine("CreateStone");
	}

	private IEnumerator CreateStone()
	{
		while (true)
		{
			GameObject instatiateObject = Instantiate(stone_);
			instatiateObject.transform.position = new Vector3(Random.Range(player_.transform.position.x + 50, 10), transform.position.y, transform.position.z);
			yield return new WaitForSeconds(createDelayS_);
		}
	}
}
