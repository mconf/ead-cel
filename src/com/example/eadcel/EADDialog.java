package com.example.eadcel;

import android.app.Dialog;
import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

class EADDialog extends GLSurfaceView implements OnClickListener
{
    private Dialog MyDialog;
    private Button button;
    EADDialog(Context pContext)
    {
            super(pContext);
            //initialize dialogs...
                      
            MyDialog = new Dialog(pContext);
            MyDialog.setContentView(R.layout.relative);
            MyDialog.setTitle("[Options]");
            //setup window appropriately...
            
            button = (Button)MyDialog.findViewById(R.id.Button01);
            try{
            button.setOnClickListener(this);
            }catch(Exception e){
            	Log.v("Java", String.format("EADDialog: erro no button.setOnClickListener(this);\n"));
            }
                 
            
     }
     void show_something()
     {
          MyDialog.show();
          Log.v("Java", String.format("TESTE\n"));
     }
     
	@Override
	public void onClick(View v) {
		// TODO Auto-generated method stub
		switch (v.getId()) {
		case R.id.Button01:
			Log.v("Java", String.format("EADDialog - onClick - Button01\n"));
			MyDialog.dismiss();
			
			//setContentView(R.layout.relative);
			break;
        }
	}
	
	@Override
	 public boolean onKeyDown(int keyCode, final KeyEvent event) {
	        //super.onKeyDown(keyCode, event);
			Log.v("Java", String.format("EADDialog - onKeyDown\n"));
		 
	        return true;
	 }
     
     

} 