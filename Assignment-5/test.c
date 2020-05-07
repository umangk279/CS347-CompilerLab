int main()
{

    int i;
    float k;
    k = 1.0;
    for(i = 0;i<10;++i)
    {
      k = k + 1;
      switch(i)
      {
          case 1:
          {
            break;
          }
          case 2:
          {
            break;
          }
          case 3:
          {
            continue;
            break;
          }
      }
    }




}