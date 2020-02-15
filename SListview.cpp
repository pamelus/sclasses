#ifndef SLISTVIEW_CPP
#define SLISTVIEW_CPP
#define _WIN32_IE               0x0500

#include <windows.h>
#include <commctrl.h>
#include "SApp.h"
#include "SWindow.h"
#include "SListview.h"

SListview::SListview(SWindow * pWin, UINT uStyle, UINT uId, UINT uExStyle):
SWindow(pWin->GetSApp(), WC_LISTVIEW, pWin->GetHwnd(), uId, WS_CHILD | LVS_SINGLESEL | LVS_SHOWSELALWAYS | uStyle, WS_EX_CLIENTEDGE | uExStyle),
hImageListBig(NULL), hImageListSmall(NULL), nColumns(0)
{
    ListView_SetExtendedListViewStyle(hwnd, LVS_EX_FULLROWSELECT);
    pWin->AddChild(this);
}

SListview::~SListview()
{
    if(hImageListBig)
        ImageList_Destroy(hImageListBig);
    if(hImageListSmall)
        ImageList_Destroy(hImageListSmall);
}

DWORD SListview::SetStyle(DWORD dwStyle)
{
    ListView_SetExtendedListViewStyle(hwnd, LVS_EX_FULLROWSELECT);
    return 0;
}

DWORD SListview::AddColumn(char * pszText, int cx)
{
    LV_COLUMN lvc; ZeroMemory(&lvc, sizeof(LV_COLUMN));
    lvc.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
    lvc.fmt = LVCFMT_LEFT;
    lvc.cx = cx;
    lvc.pszText = pszText;
    if(ListView_InsertColumn(hwnd, nColumns, &lvc) != -1)
        nColumns++;
    return 0;
}
    
DWORD SListview::DeleteColumn(int iColumn)
{
    if(ListView_DeleteColumn(hwnd, iColumn) != -1)
        nColumns--;
    return 0;
}
    
DWORD SListview::SetColumnText(int iColumn, char * pszText)
{
    LV_COLUMN lvc; ZeroMemory(&lvc, sizeof(LV_COLUMN));
    lvc.mask = LVCF_TEXT;
    lvc.pszText = pszText;
    ListView_SetColumn(hwnd, iColumn, &lvc);
    return 0;
}
    
DWORD SListview::SetColumnWidth(int iColumn, int cx)
{
    ListView_SetColumnWidth(hwnd, iColumn, cx);
    return 0;
}
    
DWORD SListview::SetColumnAligment(int iColumn, int nAlign)
{
    LV_COLUMN lvc; ZeroMemory(&lvc, sizeof(LV_COLUMN));
    lvc.mask = LVCF_FMT;
    lvc.fmt = nAlign;
    ListView_SetColumn(hwnd, iColumn, &lvc);
    return 0;
}
    
DWORD SListview::SetColumnImage(int iColumn, int iImage)
{
    LV_COLUMN lvc; ZeroMemory(&lvc, sizeof(LV_COLUMN));
    lvc.mask = LVCF_FMT;
    ListView_GetColumn(hwnd, iColumn, &lvc);
    
    lvc.mask = LVCF_IMAGE | LVCF_FMT;
    lvc.fmt |= LVCFMT_IMAGE;
    lvc.iImage = iImage;
    ListView_SetColumn(hwnd, iColumn, &lvc);
    return 0;
}

DWORD SListview::GetColumnText(int iColumn, char * pszText, DWORD dwSize) const
{
    LV_COLUMN lvc; ZeroMemory(&lvc, sizeof(LV_COLUMN));
    lvc.mask = LVCF_TEXT;
    lvc.pszText = pszText;
    lvc.cchTextMax = dwSize;
    ListView_GetColumn(hwnd, iColumn, &lvc);
    
    return 0;
}
    
DWORD SListview::GetColumnWidth(int iColumn) const
{
    return ListView_GetColumnWidth(hwnd, iColumn);
}

DWORD SListview::GetColumnAligment(int iColumn) const
{
    int align = 0;
    
    LV_COLUMN lvc; ZeroMemory(&lvc, sizeof(LV_COLUMN));
    lvc.mask = LVCF_FMT;
    ListView_GetColumn(hwnd, iColumn, &lvc);
    
    if(lvc.fmt & LVCFMT_RIGHT)
        align = ALIGN_RIGHT;
    else if(lvc.fmt & LVCFMT_CENTER)
        align = ALIGN_CENTER;
    else
        align = ALIGN_LEFT;
    return align;
}
    
DWORD SListview::GetColumnImage(int iColumn) const
{
    LV_COLUMN lvc; ZeroMemory(&lvc, sizeof(LV_COLUMN));
    lvc.mask = LVCF_IMAGE;
    ListView_GetColumn(hwnd, iColumn, &lvc);
    
    return lvc.iImage;
}    
    
DWORD SListview::BeginImage()
{
    if(hImageListBig) ImageList_Destroy(hImageListBig);
    if(hImageListSmall) ImageList_Destroy(hImageListSmall);
    hImageListBig = ImageList_Create(GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON), ILC_COLOR16, 1, 1);
    hImageListSmall = ImageList_Create(GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), ILC_COLOR16, 1, 1);
    return 0;
}

DWORD SListview::AddImage(HICON hIcon)
{
    ImageList_AddIcon(hImageListBig, hIcon);
    ImageList_AddIcon(hImageListSmall, hIcon);
    return 0;
}

DWORD SListview::AddImage(HINSTANCE hInst, UINT uImage)
{
    return this->AddImage(hInst, MAKEINTRESOURCE(uImage));
}
    
DWORD SListview::AddImage(HINSTANCE hInst, char * pszImage)
{
    HICON hIcon = LoadIcon(hInst, pszImage);
    this->AddImage(hIcon);
    DestroyIcon(hIcon);
    return 0;
}    

DWORD SListview::EndImage()
{
    ListView_SetImageList(hwnd, hImageListBig, LVSIL_NORMAL);
    ListView_SetImageList(hwnd, hImageListSmall, LVSIL_SMALL);
    return 0;
}    

DWORD SListview::AddItem(int iImage, LPARAM lParam)
{
    LV_ITEM lvi; ZeroMemory(&lvi, sizeof(LV_ITEM));
    lvi.mask = LVIF_IMAGE | LVIF_PARAM;
    lvi.iItem = ListView_GetItemCount(hwnd);
    lvi.iSubItem = 0;
    lvi.iImage = iImage;
    lvi.lParam = lParam;
    ListView_InsertItem(hwnd, &lvi);
    return 0;
}

DWORD SListview::DeleteAllItems()
{
    ListView_DeleteAllItems(hwnd);
    return 0;
}
    
DWORD SListview::DeleteItem(DWORD iItem)
{
    ListView_DeleteItem(hwnd, iItem);
    return 0;
}

DWORD SListview::SetItemText(DWORD iItem, int iColumn, char * pszText)
{
    ListView_SetItemText(hwnd, iItem, iColumn, pszText);
    return 0;
}

DWORD SListview::SetItemImage(DWORD iItem, int iImage)
{
    LV_ITEM lvi; ZeroMemory(&lvi, sizeof(LV_ITEM));
    lvi.mask = LVIF_IMAGE;
    lvi.iItem = iItem;
    lvi.iImage = iImage;
    ListView_SetItem(hwnd, &lvi);
    return 0;
}

DWORD SListview::GetItemText(DWORD iItem, int iColumn, char * pszText, DWORD dwSize) const
{
    ListView_GetItemText(hwnd, iItem, iColumn, pszText, dwSize);
    return 0;
}
    
DWORD SListview::GetItemImage(DWORD iItem) const
{
    LV_ITEM lvi; ZeroMemory(&lvi, sizeof(LV_ITEM));
    lvi.mask = LVIF_IMAGE;
    lvi.iItem = iItem;
    ListView_GetItem(hwnd, &lvi);
    return lvi.iImage;
}    
    
DWORD SListview::SetSelection(DWORD iItem)
{
    ListView_SetItemState(hwnd, iItem, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
    ListView_EnsureVisible(hwnd, iItem, FALSE);
    return 0;
}
    
DWORD SListview::GetSelection() const
{
    return ListView_GetNextItem(hwnd, (UINT)-1, LVNI_SELECTED);
}

DWORD SListview::GetItemCount() const
{
    return ListView_GetItemCount(hwnd);
}

DWORD SListview::SetTextColor(COLORREF cColor)
{
    ListView_SetTextColor(hwnd, cColor);
    return 0;
}
    
DWORD SListview::SetBkColor(COLORREF cColor)
{
    ListView_SetTextBkColor(hwnd, cColor);
    ListView_SetBkColor(hwnd, cColor);
    return 0;
}
    
COLORREF SListview::GetTextColor() const
{
    return ListView_GetTextColor(hwnd);
}
    
COLORREF SListview::GetBkColor() const
{
    return ListView_GetBkColor(hwnd);
}
    
DWORD SListview::GetItemRect(DWORD iItem, RECT * pRect) const
{
    if(!ListView_GetItemRect(hwnd, iItem, pRect, LVIR_BOUNDS))
        ZeroMemory(pRect, sizeof(RECT)); 
    return 0;
}    
    
#endif
