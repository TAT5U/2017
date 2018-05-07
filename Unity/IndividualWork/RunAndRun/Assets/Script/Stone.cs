using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Stone : MonoBehaviour 
{
	private const int kDestroyObjectPosition = -10;
	void Update()
	{
		if (transform.position.y < kDestroyObjectPosition)
		{
			Destroy(gameObject);
		}
	}


	private void OnCollisionEnter2D(Collision2D col)
	{
		if (col.gameObject.tag == "Ground")
		{
			GetComponent<Rigidbody2D>().constraints = RigidbodyConstraints2D.FreezeAll;
		}
	}

	private void OnCollisionExit2D(Collision2D col)
	{
		if (col.gameObject.tag == "Ground")
		{
			GetComponent<Rigidbody2D>().constraints = RigidbodyConstraints2D.None;
		}
	}
}
